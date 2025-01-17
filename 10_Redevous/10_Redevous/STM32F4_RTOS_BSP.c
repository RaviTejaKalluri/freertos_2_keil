#include "STM32F4_RTOS_BSP.h"
GPIO_InitTypeDef GPIO_InitStruct;


#define BSP_LED_red_BIT   (1U<<28)
#define BSP_LED_green_BIT (1U<<24)
#define BSP_LED_orange_BIT (1U<<26)
#define BSP_LED_blue_BIT  (1U<<30)


#define BSP_Probe0_BIT (1U<<0)
#define BSP_Probe1_BIT (1U<<2)
#define BSP_Probe2_BIT (1U<<4)
#define BSP_Probe3_BIT (1U<<8)

#define GPIOD_CLOCK   (1<<3)
#define GPIOC_CLOCK   (1<<2)
#define GPIOA_CLOCK   (1<<0)


#define	LED_PORT		GPIOD
#define	BSP_LED_red		 (1U<<14)
#define BSP_LED_green  (1U<<12)
#define BSP_LED_blue   (1U<<15)
#define BSP_LED_orange (1U<<13)


#define	BSP_Probe_PORT		GPIOC
#define CH0					(1U<<0)   //BSP_Probe Channel 0 PIN
#define CH1					(1U<<1)   //BSP_Probe Channel 1 PIN
#define CH2					(1U<<2)  //BSP_Probe Channel 2 PIN
#define CH3					(1U<<4)   //BSP_Probe Channel 3 PIN,PC4

#define	BSP_Button_PORT		GPIOA


void BSP_Button_Init(void){
/*User Button is connected to PA0*/

  RCC->AHB1ENR |=  GPIOA_CLOCK ;                /* enable GPIOA clock */
	BSP_Button_PORT->MODER &= ~0x00000011;        /* clear pin mode to input mode */
}

uint32_t BSP_Button_Read(void){

  return BSP_Button_PORT->IDR & 0x01;
}
void BSP_ADC1_Init(void){
  
	  /* set up pin PA1 for analog input */
    RCC->AHB1ENR |=  1;	            /* enable GPIOA clock */
    GPIOA->MODER |=  0xC;           /* PA1 analog */

      /* setup ADC1 */
    RCC->APB2ENR |= 0x00000100;     /* enable ADC1 clock */
    ADC1->CR2 = 0;                  /* SW trigger */
    ADC1->SQR3 = 1;                 /* conversion sequence starts at ch 1 */
    ADC1->SQR1 = 0;                 /* conversion sequence length 1 */
    ADC1->CR2 |= 1;                 /* enable ADC1 */
 
}

uint32_t BSP_Sensor_Read(void){
    
		ADC1->CR2 |= 0x40000000;        /* start a conversion */
    while(!(ADC1->SR & 2)) {}       /* wait for conv complete */
  
	  return ADC1->DR;

}

//*******************Start of LED APIs***************************//

void BSP_LED_Init(void)
{
  __disable_irq();
	RCC->AHB1ENR |=GPIOD_CLOCK;
	GPIOD->MODER |= BSP_LED_red_BIT|BSP_LED_green_BIT|BSP_LED_orange_BIT|BSP_LED_blue_BIT;
  __enable_irq();

}
 void BSP_LED_blueOn(void)
 {
	 GPIOD->ODR |=BSP_LED_blue;
	 
 }

 void BSP_LED_blueOff(void)
 {
	 GPIOD->ODR &= ~BSP_LED_blue;
	 
 }


 
  void BSP_LED_orangeOn(void)
 {
	 GPIOD->ODR |=BSP_LED_orange;
	 
 }

 void BSP_LED_orangeOff(void)
 {
	 GPIOD->ODR &= ~BSP_LED_orange;
	 
 }
 
  void BSP_LED_greenOn(void)
 {
	 GPIOD->ODR |=BSP_LED_green;
	 
 }

 void BSP_LED_greenOff(void)
 {
	 GPIOD->ODR &= ~BSP_LED_green;
	 
 }

 void BSP_LED_redOn(void)
 {
	 GPIOD->ODR |=BSP_LED_red;
	 
 }

 void BSP_LED_redOff(void)
 {
	 GPIOD->ODR &= ~BSP_LED_red;
	 
 }
  void BSP_LED_blueToggle(void)
 {
	 GPIOD->ODR ^=BSP_LED_blue;
	 
 }

 void BSP_LED_greenToggle(void)
 {
	 GPIOD->ODR ^=BSP_LED_green;
	 
 }
 
 void BSP_LED_redToggle(void)
 {
	 GPIOD->ODR ^=BSP_LED_red;
	 
 }

 void BSP_LED_orangeToggle(void)
 {
	 GPIOD->ODR ^=BSP_LED_orange;
	 
 }


 void BSP_LED_AllToggle(void)
 {
	 GPIOD->ODR ^= BSP_LED_orange|BSP_LED_green|BSP_LED_red|BSP_LED_blue;
 }
//*******************End of LED APIs***************************//

//*******************Start of Probe APIs***************************//
void BSP_Probe_Init(void)
{
  __disable_irq();
	RCC->AHB1ENR |= GPIOC_CLOCK;
	BSP_Probe_PORT->MODER |= BSP_Probe0_BIT|BSP_Probe1_BIT|BSP_Probe2_BIT|BSP_Probe3_BIT;
  __enable_irq();

}


void BSP_Probe_CH0(){

	 BSP_Probe_PORT->ODR ^= CH0;
}

void BSP_Probe_CH1(){

	 BSP_Probe_PORT->ODR ^= CH1;
}

void BSP_Probe_CH2(){

	 BSP_Probe_PORT->ODR ^= CH2;
}

void BSP_Probe_CH3(){

	 BSP_Probe_PORT->ODR ^= CH3;
}




//*******************Start of SystemClockConfig API's******************/
void SystemClock_Config80Mhz(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

 HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
  
 

}
//*******************************End of SystemClockConfig APIs**************/




//*******************************Start of TIMERS APIs**************/


TIM_HandleTypeDef htim2;


/* TIM2 init function */
void TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 16000; // Scale down to milliseconds
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 1;   //ms
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  
	HAL_TIM_Base_Init(&htim2);
  
  
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);
 
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  
	HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);
  

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
 
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* Peripheral interrupt Deinit*/
    HAL_NVIC_DisableIRQ(TIM2_IRQn);


  }

} 

void TIM2_Init_Start(void)
{
	 TIM2_Init();
	
   HAL_TIM_Base_Start_IT(&htim2);

}


 HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  /*Init and configure the TIM2 to have interrupt in 1ms time basis*/
  TIM2_Init_Start();
  /* Return function status */
  return HAL_OK;
}

int counter2;
/**
* @brief This function handles TIM2 global interrupt.
*/
void TIM2_IRQHandler(void)
{
  
	counter2++;  /*For testing*/
	HAL_IncTick();
  HAL_TIM_IRQHandler(&htim2);
 
}


//------------Milliseconds delay using TIMER2-------------//
 void DelayMs(__IO uint32_t Delay)
{
  uint32_t tickstart = 0U;
  tickstart = HAL_GetTick();
  while((HAL_GetTick() - tickstart) < Delay){}
  
}
//**********************Start of ADC APIs**************************//
ADC_HandleTypeDef hadc1;


 void ADC1_Init(void)
{
	__HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = ENABLE;
  hadc1.Init.NbrOfDiscConversion = 1;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  
	
	HAL_ADC_Init(&hadc1);
  
  

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
  

}
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(hadc->Instance==ADC1)
  {

    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  }

}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{

  if(hadc->Instance==ADC1)
  {

    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC1 GPIO Configuration    
    PA4     ------> ADC1_IN4 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

  }
 

}
//**********************End of ADC APIs**************************//


//**********************Start of ST7735 LCD APIs*********************/
void ST7735_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;



  __GPIOB_CLK_ENABLE();



  /*Configure GPIO pins : PB10 PB12 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

SPI_HandleTypeDef hspi2;

/* SPI2 init function */
void ST7735_SPI_Init(void)
{

  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_1LINE;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLED;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
  hspi2.Init.CRCPolynomial = 10;
  HAL_SPI_Init(&hspi2);

}

void spi2_8b_init(void){
 hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
 HAL_SPI_Init(&hspi2);

}
void spi2_16b_init(void){
 hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
 HAL_SPI_Init(&hspi2);
}	
	
void lcd7735_senddata(unsigned char data) {
  HAL_SPI_Transmit(&hspi2, &data,1,0x1);
}
void lcd7735_send16bData(uint8_t msb,uint8_t lsb) {
	uint8_t masData[]={lsb,msb};
	HAL_SPI_Transmit(&hspi2,masData,1,0x1);
}



void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{

  GPIO_InitTypeDef GPIO_InitStruct;
 
 
    __SPI2_CLK_ENABLE();
  
    /**SPI2 GPIO Configuration    
    PB13     ------> SPI2_SCK
    PB15     ------> SPI2_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  

}

void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{



    __SPI2_CLK_DISABLE();
  
    /**SPI2 GPIO Configuration    
    PB13     ------> SPI2_SCK
    PB15     ------> SPI2_MOSI 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_15);
}


static int16_t _width = ST7735_TFTWIDTH;
static int16_t _height = ST7735_TFTHEIGHT;
uint32_t StX=0; 
uint32_t StY=0; 
uint16_t StTextColor = BLUE;
static uint8_t ColStart, RowStart; 
void static writedata(uint8_t d);
void static setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void static writecommand(uint8_t c) ;

void ST7735_SetCursor(uint32_t newX, uint32_t newY);
void standard_Init_Cmd(void);


void ST7735_Init(void) {

 ST7735_GPIO_Init();
 ST7735_SPI_Init();
 standard_Init_Cmd();
	
  ST7735_SetCursor(0,0);
  StTextColor = BLUE;
  ST7735_FillScreen(BLACK);        
}

void ST7735_SetCursor(uint32_t newX, uint32_t newY){
  if((newX > 20) || (newY > 15)){       
    return;                           
  }
  StX = newX;
  StY = newY;
}

void ST7735_FillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  if((x >= _width) || (y >= _height)) return;
  if((x + w - 1) >= _width)  w = _width  - x;
  if((y + h - 1) >= _height) h = _height - y;

  setAddrWindow(x, y, x+w-1, y+h-1);

  for(y=h; y>0; y--) {
    for(x=w; x>0; x--) {
      writedata(hi);
      writedata(lo);
    }
  }
}

void ST7735_FillScreen(uint16_t color) {
  ST7735_FillRect(0, 0, _width, _height, color);  
}

void static writecommand(uint8_t c) {
  LCD_DC0; //Set DC low
  lcd7735_senddata(c);
}
void static writedata(uint8_t d) {
  LCD_DC1;//Set DC HIGH
   lcd7735_senddata(d);
}

void static setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {

  writecommand(ST7735_CASET); // Column addr set
  writedata(0x00);
  writedata(x0+ColStart);     // XSTART
  writedata(0x00);
  writedata(x1+ColStart);     // XEND

  writecommand(ST7735_RASET); // Row addr set
  writedata(0x00);
  writedata(y0+RowStart);     // YSTART
  writedata(0x00);
  writedata(y1+RowStart);     // YEND

  writecommand(ST7735_RAMWR); // write to RAM
}


void standard_Init_Cmd(void)
{
	LCD_CS0;            // CS=0   
  LCD_RST0;           // RST=0 

  DelayMs(10);      

  LCD_RST1;           // RST=1
  DelayMs(10);      

   
   lcd7735_sendCmd(0x11); 

   DelayMs(120);      

   lcd7735_sendCmd (0x3A); //Set Color mode
   lcd7735_sendData(0x05); //16 bits
	 lcd7735_sendCmd (0x36);
	 lcd7735_sendData(0x14);
	 lcd7735_sendCmd (0x29);//Display on
}

void static pushColor(uint16_t color) {
  writedata((uint8_t)(color >> 8));
  writedata((uint8_t)color);
}

void ST7735_DrawPixel(int16_t x, int16_t y, uint16_t color) {

  if((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;

  setAddrWindow(x,y,x,y);

  pushColor(color);
}

void ST7735_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((y+h-1) >= _height) h = _height-y;
  setAddrWindow(x, y, x, y+h-1);

  while (h--) {
    writedata(hi);
    writedata(lo);
  }
}

void ST7735_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
  uint8_t hi = color >> 8, lo = color;

  // Rudimentary clipping
  if((x >= _width) || (y >= _height)) return;
  if((x+w-1) >= _width)  w = _width-x;
  setAddrWindow(x, y, x+w-1, y);

  while (w--) {
    writedata(hi);
    writedata(lo);
  }
}

void ST7735_DrawBitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h){
  int16_t skipC = 0;                      
  int16_t originalWidth = w;              
  int i = w*(h - 1);

  if((x >= _width) || ((y - h + 1) >= _height) || ((x + w) <= 0) || (y < 0)){
    return;                             
  }
  if((w > _width) || (h > _height)){    
   
    return;
  }
  if((x + w - 1) >= _width){            
    skipC = (x + w) - _width;           
    w = _width - x;
  }
  if((y - h + 1) < 0){                  
    i = i - (h - y - 1)*originalWidth;  
    h = y + 1;
  }
  if(x < 0){                            
    w = w + x;
    skipC = -1*x;                       
    i = i - x;                          
    x = 0;
  }
  if(y >= _height){                     
    h = h - (y - _height + 1);
    y = _height - 1;
  }

  setAddrWindow(x, y-h+1, x+w-1, y);

  for(y=0; y<h; y=y+1){
    for(x=0; x<w; x=x+1){
                                        
      writedata((uint8_t)(image[i] >> 8));
                                        
      writedata((uint8_t)image[i]);
      i = i + 1;                       
    }
    i = i + skipC;
    i = i - 2*originalWidth;
  }
}

void ST7735_DrawCharS(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; 
  int32_t i, j;
  if((x >= _width)            || 
     (y >= _height)           || 
     ((x + 5 * size - 1) < 0) || 
     ((y + 8 * size - 1) < 0))   
    return;

  for (i=0; i<6; i++ ) {
    if (i == 5)
      line = 0x0;
    else
      line = Font[(c*5)+i];
    for (j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) 
          ST7735_DrawPixel(x+i, y+j, textColor);
        else {  
          ST7735_FillRect(x+(i*size), y+(j*size), size, size, textColor);
        }
      } else if (bgColor != textColor) {
        if (size == 1) // default size
          ST7735_DrawPixel(x+i, y+j, bgColor);
        else {  // big size
          ST7735_FillRect(x+i*size, y+j*size, size, size, bgColor);
        }
      }
      line >>= 1;
    }
  }
}

void ST7735_DrawChar(int16_t x, int16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size){
  uint8_t line; // horizontal row of pixels of character
  int32_t col, row, i, j;// loop indices
  if(((x + 5*size - 1) >= _width)  || // Clip right
     ((y + 8*size - 1) >= _height) || // Clip bottom
     ((x + 5*size - 1) < 0)        || // Clip left
     ((y + 8*size - 1) < 0)){         // Clip top
    return;
  }

  setAddrWindow(x, y, x+6*size-1, y+8*size-1);

  line = 0x01;        // print the top row first
  // print the rows, starting at the top
  for(row=0; row<8; row=row+1){
    for(i=0; i<size; i=i+1){
      // print the columns, starting on the left
      for(col=0; col<5; col=col+1){
        if(Font[(c*5)+col]&line){
          // bit is set in Font, print pixel(s) in text color
          for(j=0; j<size; j=j+1){
            pushColor(textColor);
          }
        } else{
          // bit is cleared in Font, print pixel(s) in background color
          for(j=0; j<size; j=j+1){
            pushColor(bgColor);
          }
        }
      }
      // print blank column(s) to the right of character
      for(j=0; j<size; j=j+1){
        pushColor(bgColor);
      }
    }
    line = line<<1;   // move up to the next row
  }
}
uint16_t ST7735_Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3);
}

uint32_t ST7735_DrawString(uint16_t x, uint16_t y, char *pt, int16_t textColor){
  uint32_t count = 0;
  if(y>15) return 0;
  while(*pt){
    ST7735_DrawCharS(x*6, y*10, *pt, textColor, BLACK, 1);
    pt++;
    x = x+1;
    if(x>20) return count;  // number of characters printed
    count++;
  }
  return count;  // number of characters printed
}

int32_t Ymax,Ymin,X;        // X goes from 0 to 127
int32_t Yrange; //YrangeDiv2;


void ST7735_PlotClear(int32_t ymin, int32_t ymax){
  ST7735_FillRect(0, 32, 128, 128, ST7735_Color565(228,228,228)); // light grey
  if(ymax>ymin){
    Ymax = ymax;
    Ymin = ymin;
    Yrange = ymax-ymin;
  } else{
    Ymax = ymin;
    Ymin = ymax;
    Yrange = ymax-ymin;
  }
  //YrangeDiv2 = Yrange/2;
  X = 0;
}
int TimeIndex;               
int32_t Ymax, Ymin, Yrange;  
uint16_t PlotBGColor; 

void ST7735_SimplePlotPoint(int32_t y)
{
		int32_t j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;
  j = 32+(127*(Ymax-y))/Yrange;
  if(j<32) j = 32;
  if(j>159) j = 159;
  ST7735_DrawPixel(X,   j,  BLUE);
  ST7735_DrawPixel(X+1, j,  BLUE);
  ST7735_DrawPixel(X,   j+1,BLUE);
  ST7735_DrawPixel(X+1, j+1,BLUE);
}

void ST7735_PlotPoint(int32_t data1, uint16_t color1){
  data1 = ((data1 - Ymin)*100)/Yrange;
  if(data1 > 98){
    data1 = 98;
    color1 = RED;
  }
  if(data1 < 0){
    data1 = 0;
    color1 = RED;
  }
  ST7735_DrawPixel(TimeIndex + 11, 116 - data1, color1);
  ST7735_DrawPixel(TimeIndex + 11, 115 - data1, color1);
}
void ST7735_PlotIncrement(void){
  TimeIndex = TimeIndex + 1;
  if(TimeIndex > 99){
    TimeIndex = 0;
  }
  ST7735_DrawFastVLine(TimeIndex + 11, 17, 100, PlotBGColor);
}

int32_t lastj=0;

void ST7735_PlotLine(int32_t y)
{
	int32_t i,j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;
  // X goes from 0 to 127
  // j goes from 159 to 32
  // y=Ymax maps to j=32
  // y=Ymin maps to j=159
  j = 32+(127*(Ymax-y))/Yrange;
  if(j < 32) j = 32;
  if(j > 159) j = 159;
  if(lastj < 32) lastj = j;
  if(lastj > 159) lastj = j;
  if(lastj < j){
    for(i = lastj+1; i<=j ; i++){
      ST7735_DrawPixel(X,   i,   BLUE) ;
      ST7735_DrawPixel(X+1, i,   BLUE) ;
    }
  }else if(lastj > j){
    for(i = j; i<lastj ; i++){
      ST7735_DrawPixel(X,   i,   BLUE) ;
      ST7735_DrawPixel(X+1, i,   BLUE) ;
    }
  }else{
    ST7735_DrawPixel(X,   j,   BLUE) ;
    ST7735_DrawPixel(X+1, j,   BLUE) ;
  }
  lastj = j;
}

void ST7735_PlotBar(int32_t y){
int32_t j;
  if(y<Ymin) y=Ymin;
  if(y>Ymax) y=Ymax;

  j = 32+(127*(Ymax-y))/Yrange;
  ST7735_DrawFastVLine(X, j, 159-j,BLACK);

}

void ST7735_PlotNext(void){
  if(X==127){
    X = 0;
  } else{
    X++;
  }
}

void lcd7735_sendCmd(unsigned char cmd) {
   LCD_DC0; //Set DC low
   lcd7735_senddata(cmd);
}

void lcd7735_sendData(unsigned char data) {
   LCD_DC1;//Set DC HIGH
   lcd7735_senddata(data);
}
//Define Screen area
void lcd7735_at(unsigned char startX, unsigned char startY, unsigned char stopX, unsigned char stopY) {
	lcd7735_sendCmd(0x2A);
	LCD_DC1;
	lcd7735_senddata(0x00);
	lcd7735_senddata(startX);
	lcd7735_senddata(0x00);
	lcd7735_senddata(stopX);

	lcd7735_sendCmd(0x2B);
	LCD_DC1;
	lcd7735_senddata(0x00);
	lcd7735_senddata(startY);
	lcd7735_senddata(0x00); 
	lcd7735_senddata(stopY);
}




void ST7735_Drawaxes(uint16_t axisColor, uint16_t bgColor, char *xLabel,char *yLabel1, uint16_t label1Color, char *yLabel2, uint16_t label2Color,int32_t ymax, int32_t ymin)
	{
  int i;

  Ymax = ymax;
  Ymin = ymin;
  Yrange = Ymax - Ymin;
  TimeIndex = 0;
  PlotBGColor = bgColor;
  ST7735_FillRect(0, 0, 128, 160, bgColor);
  ST7735_DrawFastHLine(10, 140, 101, axisColor);
  ST7735_DrawFastVLine(10, 17, 124, axisColor);
  for(i=20; i<=110; i=i+10){
    ST7735_DrawPixel(i, 141, axisColor);
  }
  for(i=17; i<120; i=i+10){
    ST7735_DrawPixel(9, i, axisColor);
  }
  i = 50;
  while((*xLabel) && (i < 100)){
    ST7735_DrawChar(i, 145, *xLabel, axisColor, bgColor, 1);
    i = i + 6;
    xLabel++;
  }
  if(*yLabel2){ // two labels
    i = 26;
    while((*yLabel2) && (i < 50)){
      ST7735_DrawChar(0, i, *yLabel2, label2Color, bgColor, 1);
      i = i + 8;
      yLabel2++;
    }
    i = 82;
  }else{ // one label
    i = 42;
  }
  while((*yLabel1) && (i < 120)){
   ST7735_DrawChar(0, i, *yLabel1, label1Color, bgColor, 1);
    i = i + 8;
    yLabel1++;
  }
}



