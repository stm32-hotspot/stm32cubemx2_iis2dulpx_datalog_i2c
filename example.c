/**
  ******************************************************************************
  * file           : example.c
  * brief          : example program body
  *                   Called by the main after system initialization
  ******************************************************************************
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "example.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables */
iis2dulpx_object_t *pIis2dulpx0; /* pointer referencing the IIS2DULPX object instance */
iis2dulpx_axes_t gAccData; /* This variable store the acceleratometer measurement (unit: deg mg) */
/** ########## Step 1 ##########
  * The init of IIS2DULPX is triggered by the applicative code

  */
app_status_t app_init(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* Retrieve and store the IIS2DULPX object pointer */
  pIis2dulpx0 = MX_IIS2DULPX_getobject();
  /* Initialize the IIS2DULPX device 0 */
  if (iis2dulpx_drv_init(pIis2dulpx0, MX_IIS2DULPX) != 0)
  {
    PRINTF("[ERROR] Step 1: IIS2DULPX sensor init error\r\n");
    goto _app_init_exit;
  }
  PRINTF("[INFO] Step 1: IIS2DULPX sensor init completed\r\n");
  /* IIS2DULPX device 0: enable the accelerometer feature */
  if (iis2dulpx_drv_acc_enable(pIis2dulpx0) != 0)
  {
    PRINTF("[ERROR] Step 1: Enabling the ACC feature error\r\n");
    goto _app_init_exit;
  }
    PRINTF("[INFO] Step 1: Enabling the ACC feature completed\r\n");
  return_status = EXEC_STATUS_INIT_OK;
  
_app_init_exit:
  return return_status;
}

/**
  * ########## Step 2 ##########
  * Gets the values from IIS2DULPX.
  * The values are displayed on the terminal.
  * output: EXEC_STATUS_OK if OK, EXEC_STATUS_ERROR in case of error
  */
app_status_t app_process(void)
{
  app_status_t return_status = EXEC_STATUS_ERROR;
  /* IIS2DULPX device 0: get the acceleration value and print it */
  if (iis2dulpx_drv_acc_get_axes(pIis2dulpx0, &gAccData) != 0)
  {
    PRINTF("[ERROR] Step 2: Reading acceleration error\n");
    goto _app_process_exit;
  }
  PRINTF("[INFO] Step 2: ACC X=%" PRIi32 " Y=%" PRIi32 " Z=%" PRIi32 "\n", (int32_t)gAccData.x_axis,
         (int32_t)gAccData.y_axis, (int32_t)gAccData.z_axis);
  return_status = EXEC_STATUS_OK;

_app_process_exit:
  return return_status;
}

/** ########## Step 3 ##########
  * In this example, app_deinit is never called and is provided as a reference only.
  */
app_status_t app_deinit(void)
{
  iis2dulpx_drv_deinit(pIis2dulpx0);

  return EXEC_STATUS_OK;
}
