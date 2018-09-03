/**
* MIT License
*
* Copyright (c) 2018 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
*
 * \file  main_xmc4500_sample.c
 *
 * \brief   This sample demonstrates OPTIGA use cases.
 *
 */

/*************************************************************************
 *  required includes
*************************************************************************/

#include <DAVE.h>			//Declarations from DAVE Code Generation (includes SFR declaration)
#include "optiga/comms/optiga_comms.h"
#include "optiga/optiga_util.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"
#include "optiga/common/AuthLibSettings.h"
#include "Helper.h"
/*************************************************************************
 *  main_xmc4500.c
*************************************************************************/


/*************************************************************************
*  defines
*************************************************************************/

/*************************************************************************
*  function prototypes
*************************************************************************/
static int32_t optiga_init(void);
extern optiga_lib_status_t  example_optiga_crypt_ecc_generate_keypair(void);
extern optiga_lib_status_t  example_optiga_crypt_ecdh(void);
extern optiga_lib_status_t  example_optiga_crypt_ecdsa_sign(void);
extern optiga_lib_status_t  example_optiga_crypt_ecdsa_verify(void);
extern optiga_lib_status_t  example_optiga_crypt_hash(void);
extern optiga_lib_status_t  example_optiga_crypt_random(void);
extern optiga_lib_status_t  example_optiga_crypt_tls_prf_sha256(void);
extern optiga_lib_status_t  example_optiga_util_read_data(void);
extern optiga_lib_status_t  example_optiga_util_write_data(void);
extern optiga_lib_status_t  example_authenticate_chip(void);

extern optiga_lib_status_t asn1_to_ecdsa_rs(const uint8_t * asn1, size_t asn1_len,
											uint8_t * rs, size_t * rs_len);
/*************************************************************************
*  Global
*************************************************************************/
optiga_comms_t optiga_comms = {(void*)&ifx_i2c_context_0,NULL,NULL, OPTIGA_COMMS_SUCCESS};

/*************************************************************************
*  functions
*************************************************************************/

static int32_t optiga_init(void)
{
	int32_t status = (int32_t) OPTIGA_LIB_ERROR;

	do
	{
		status = optiga_util_open_application(&optiga_comms);
		if(OPTIGA_LIB_SUCCESS != status)
		{
			XMC_DEBUG( ("Failure: CmdLib_OpenApplication(): 0x%04X\n\r", status) );
			break;
		}

		status = OPTIGA_LIB_SUCCESS;
	} while(0);

	return status;
}

/**
 * This function is the entry point of sample.
 *
 * \retval  
 *  0 on success
 *  1 on failure
 */
int main(Void)
{
	//Return value 
	optiga_lib_status_t return_status = OPTIGA_LIB_ERROR;
    DAVE_STATUS_t status;

	// Initialisation of DAVE Apps
    status = DAVE_Init(); /* Initialization of DAVE APPs  */
    if (status == DAVE_STATUS_FAILURE) 
    {
        /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
        XMC_DEBUG("DAVE APPs initialization failed\n");

        while (1U)
        {

        }
    }

	do
	{
        if (OPTIGA_LIB_SUCCESS != optiga_init())
        {
        	break;
        }

#ifdef MODULE_ENABLE_ONE_WAY_AUTH
		Print_Stringline("***Starting Authentication use cases***");
		//Demonstrate Chip Authentication
		return_status = example_authenticate_chip();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}
		Print_Stringline("***Exiting Authentication use cases***");
#endif // MODULE_ENABLE_ONE_WAY_AUTH

#ifdef MODULE_ENABLE_TOOLBOX

		Print_Stringline("***Starting Tool Box use cases***");
		//Demonstrate Toolbox - Generate Keypair
		return_status = example_optiga_crypt_ecc_generate_keypair();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Toolbox - Calculate Sign
		return_status = example_optiga_crypt_ecdsa_sign();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Toolbox - CalcHash
		return_status = example_optiga_crypt_hash();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Toolbox - VerifySign
		return_status = example_optiga_crypt_ecdsa_verify();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Toolbox - CalculateSharedSecret
		return_status = example_optiga_crypt_ecdh();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Toolbox - DeriveKey
		return_status = example_optiga_crypt_tls_prf_sha256();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}
		Print_Stringline("***Exiting Tool Box use cases***");
#endif/*MODULE_ENABLE_TOOLBOX*/

#ifdef MODULE_ENABLE_READ_WRITE
        Print_Stringline("***Starting Read/Write use cases***");
		//Demonstrate Write General Purpose Data
		return_status = example_optiga_util_write_data();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}

		//Demonstrate Read General Purpose Data
        return_status = example_optiga_util_read_data();
		if(OPTIGA_LIB_SUCCESS != return_status)
		{
			break;
		}
		Print_Stringline("***Exiting Read/Write use cases***");
#endif/*MODULE_ENABLE_READ_WRITE*/
		return_status = OPTIGA_LIB_SUCCESS;
	}while(FALSE);

    //Close IFX I2C Protocol and switch off the security chip
    return_status = optiga_comms_close(&optiga_comms);
    if(E_COMMS_SUCCESS != return_status)
    {
        PrintLine_ErrorCode("Failure: optiga_comms_close", return_status);
    }
    Print_Stringline("Device closed");

	return ((return_status == E_COMMS_SUCCESS)? 0:1);
}


