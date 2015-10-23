#if 0
#include "i2c.h"

static I2C_type I2C_list[] =
{
		{ &I2C1_CR1, &I2C1_CR2, &I2C1_OAR1, &I2C1_OAR2, &I2C1_DR, &I2C1_SR1, &I2C1_SR2,  &I2C1_CCR, &I2C1_TRISE, NULL, NULL },
		{ &I2C2_CR1, &I2C2_CR2, &I2C2_OAR1, &I2C2_OAR2, &I2C2_DR, &I2C2_SR1, &I2C2_SR2,  &I2C2_CCR, &I2C2_TRISE, NULL, NULL },

};

static uint32_t _errorCount;
static uint32_t _retryCount = 1000;

I2C_type* I2C_GetInstance(I2Cn i2c_number)
{
	return &I2C_list[i2c_number];
}


static void I2C_ClearAF(I2C_type* i2c)
{
    *i2c->pI2C_SR1 &= ~I2C_SR1_AF;
}
static void I2C_ClearARLO(I2C_type* i2c)
{
    *i2c->pI2C_SR1 &= ~I2C_SR1_ARLO;
}
static void I2C_ClearBusError(I2C_type* i2c)
{
    *i2c->pI2C_SR1 &= ~I2C_SR1_BERR;
}

static void I2C_ClearTimeout(I2C_type* i2c)
{
    *i2c->pI2C_SR1 &= ~I2C_SR1_TIMEOUT;
}



static BOOL I2C_IsTimeout(I2C_type* i2c)
{
	return *i2c->pI2C_SR1 & I2C_SR1_TIMEOUT;

}

static BOOL I2C_IsAF(I2C_type* i2c)
{
	return *i2c->pI2C_SR1 & I2C_SR1_AF;
}

static BOOL I2C_IsARLO(I2C_type* i2c)
{
	return *i2c->pI2C_SR1 & I2C_SR1_ARLO;
}

static BOOL I2C_IsBusError(I2C_type* i2c)
{
	return *i2c->pI2C_SR1 & I2C_SR1_BERR;
}

static BOOL I2C_is_error(I2C_type* i2c)
{
	BOOL isError = FALSE;
	if (I2C_IsARLO(i2c))
	{
		I2C_ClearARLO(i2c);
		isError = TRUE;
	}
	if (I2C_IsAF(i2c))
	{
		I2C_ClearAF(i2c);
		isError = TRUE;
	}
	if (I2C_IsTimeout(i2c))
	{
		I2C_ClearTimeout(i2c);
		isError = TRUE;
	}
	if (I2C_IsBusError(i2c))
	{
		I2C_ClearBusError(i2c);
		isError = TRUE;
	}

	return isError;

}

static BOOL I2C_WaitStatus(I2C_type* i2c, I2C_STATUS_MASK status_mask, BOOL set)
{
	BOOL rc = FALSE;
	uint32_t retryCount = _retryCount;

	while (--retryCount)
	{
		uint32_t status = *i2c->pI2C_SR1 | (*i2c->pI2C_SR2 & 0xff) << 16;

		BOOL is_set = (status & status_mask) == status_mask;
		if (set == is_set)
		{
			rc = TRUE;
			break;
		}

		if (I2C_is_error(i2c))
		{
			break;
		}

	}

	if (!rc)
	{
		++_errorCount;
	}

	return rc;

}

static void I2C_EnableACK(I2C_type* i2c, BOOL on)
{
	if (on)
	{
		*i2c->pI2C_CR1 |= I2C_CR1_ACK;
	}
	else
	{
		*i2c->pI2C_CR1 &= ~I2C_CR1_ACK;
	}

}

static void I2C_SendStop(I2C_type* i2c, BOOL on)
{
	if (on)
	{
		*i2c->pI2C_CR1 |= I2C_CR1_STOP;
	}
	else
	{
		*i2c->pI2C_CR1 &= ~I2C_CR1_STOP;
	}

}

static void I2C_SendStart(I2C_type* i2c, BOOL on)
{
	if (on)
	{
		*i2c->pI2C_CR1 |= I2C_CR1_START;
	}
	else
	{
		*i2c->pI2C_CR1 &= ~I2C_CR1_START;
	}

}

static void I2C_Send7bitAddress(I2C_type* i2c, uint8_t slaveAddr, BOOL isWrite)
{
	if (isWrite)
	{
		slaveAddr &= ~0x1;
	}
	else
	{
		slaveAddr |= 0x1;
	}
	*i2c->pI2C_DR = slaveAddr;
}

static void I2C_SendByte(I2C_type* i2c, uint8_t data)
{
	*i2c->pI2C_DR = data;
}

static uint8_t I2C_ReceiveByte(I2C_type* i2c)
{
	return *i2c->pI2C_DR;
}

static BOOL I2C_MasterRead_Internal(I2C_type* i2c, uint8_t* data,
		uint32_t data_size, uint8_t slave_addr, uint8_t* reg_addr)
{
	if (data_size == 0)
	{
		return TRUE;
	}

	if (!I2C_WaitStatus(i2c, I2C_BUSY, FALSE))
	{
		return FALSE;
	}

	if (reg_addr)
	{
		I2C_SendStart(i2c, TRUE);

		if (!I2C_WaitStatus(i2c, MASTER_EV5, TRUE)) //BSY MSL SB
			return FALSE;

		I2C_Send7bitAddress(i2c, slave_addr, TRUE);

		if (!I2C_WaitStatus(i2c, MASTER_EV6_TRA, TRUE)) //MSL | BUSY | ADDR | TXE | TRA
			return FALSE;

		I2C_SendByte(i2c, *reg_addr);

		if (!I2C_WaitStatus(i2c, MASTER_EV8_2, TRUE)) //TRA, BUSY, MSL, TXE and BTF
			return FALSE;

	}

	I2C_SendStart(i2c, TRUE);

	if (!I2C_WaitStatus(i2c, MASTER_EV5, TRUE)) //BSY MSL SB
		return FALSE;

	I2C_Send7bitAddress(i2c, slave_addr, FALSE);

	if (!I2C_WaitStatus(i2c, MASTER_EV6_RECV, TRUE)) //MSL | BUSY | ADDR
		return FALSE;

	//////////////////////////////////////////////
	if (data_size > 1) // && _dmaRxStream)
	{
		//return I2C_ReceiveDMA(i2c, data, data_size);
		return FALSE; //TODO!!!
	}
	else
	{
		while (data_size)
		{
			if (data_size == 1)
			{
				I2C_EnableACK(i2c, FALSE);
				I2C_SendStop(i2c, TRUE);
			}
			if (!I2C_WaitStatus(i2c, MASTER_EV7, TRUE)) //or RXNE //MASTER_EV7
			{
				return FALSE;
			}

			*data = I2C_ReceiveByte(i2c);
			data++;
			data_size--;

		}

		I2C_EnableACK(i2c, TRUE);
		return TRUE;
	}

}

BOOL I2C_MasterRead(I2C_type* i2c, uint8_t* data, uint32_t data_size,
		uint8_t slave_addr, uint8_t* reg_addr)
{
	if (!i2c->errorCallBack)
	{
		return I2C_MasterRead_Internal(i2c, data, data_size, slave_addr, reg_addr);
	}
	else
	{
		while (!I2C_MasterRead_Internal(i2c, data, data_size, slave_addr, reg_addr))
		{
			i2c->errorCallBack(i2c->errorCallBackArg);
		}

		return TRUE;
	}

}

static BOOL I2C_MasterWriteInternal(I2C_type* i2c, uint8_t* data, uint32_t data_size,	uint8_t slave_addr, uint8_t* preg_addr)
{
	if (data_size == 0)
	{
		return TRUE;
	}

	if (!I2C_WaitStatus(i2c, I2C_BUSY, FALSE))
	{
		return FALSE;
	}

	I2C_SendStart(i2c, TRUE);

	if (!I2C_WaitStatus(i2c, MASTER_EV5, TRUE))
		return FALSE;

	I2C_Send7bitAddress(i2c, slave_addr, TRUE);

	if (!I2C_WaitStatus(i2c, MASTER_EV6_TRA, TRUE)) //MSL | BUSY | ADDR | TXE | TRA
		return FALSE;

	////////////////////////////////////////////////////////////////////////////
	if (preg_addr)
	{
		I2C_SendByte(i2c, *preg_addr);
		if (!I2C_WaitStatus(i2c, MASTER_EV8_2, TRUE)) //TRA, BUSY, MSL, TXE and BTF
			return FALSE;
	}
	////////////////////////////////////////////////////////////////////////////

	if (data_size == 1)// || !_dmaTxStream)
	{
		I2C_SendByte(i2c, *data);

		if (!I2C_WaitStatus(i2c, MASTER_EV8, TRUE)) //TRA, BUSY, MSL, TXE and BTF
			return FALSE;

		I2C_SendStop(i2c, TRUE);

		return TRUE;

	}
	else
	{
		//return I2C_SendDMA(i2c, data, data_size);
		return FALSE; //TODO!!!
	}

}


BOOL I2C_MasterWrite (I2C_type* i2c, uint8_t* data, uint32_t data_size, uint8_t slave_addr, uint8_t* preg_addr)
{
    if (!i2c->errorCallBack)
    {
        return I2C_MasterWriteInternal(i2c, data, data_size, slave_addr, preg_addr);
    }
    else
    {
        while (!I2C_MasterWriteInternal (i2c, data, data_size, slave_addr, preg_addr))
        {
			i2c->errorCallBack(i2c->errorCallBackArg);
        }
        return TRUE;
    }

}


#endif
