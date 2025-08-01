let f28e12x_boot =[
    {name: "0x00", displayName:"(PARALLEL) D0-D7=GPIO(0,1,3,4,5,24,28,29) , MCU-Control=GPIO224 , Host-Control=GPIO242"},
    {name: "0x20", displayName:"(PARALLEL) D0-D7=GPIO(0-7) , MCU-Control=GPIO12 , Host-Control=GPIO13"},
    {name: "0x01", displayName:"(SCI) SCIATX=GPIO29 , SCIARX=GPIO28"},
    {name: "0x21", displayName:"(SCI) SCIATX=GPIO1 , SCIARX=GPIO0"},
    {name: "0x61", displayName:"(SCI) SCIATX=GPIO7 , SCIARX=GPIO3"},
    {name: "0x81", displayName:"(SCI) SCIATX=GPIO16 , SCIARX=GPIO3"},
    {name: "0x03", displayName:"(FLASH) Flash-Entry-Address=0x00080000 , CPU1 Bank 0 , Sector 0"},
    {name: "0x23", displayName:"(FLASH) Flash-Entry-Address=0x00088000 , CPU1 Bank 0 , Sector 32"},
    {name: "0x04", displayName:"(WAIT) Watchdog is Enabled"},
    {name: "0x24", displayName:"(WAIT) Watchdog is Disabled"},
    {name: "0x05", displayName:"(RAM) RAM-Entry-Point-Address=0x00000000"},
    {name: "0x06", displayName:"(SPI) SPIA_PICO=GPIO24 , SPIA_POCI=GPIO1 , SPIA_CLK=GPIO3 , SPIA_PTE=GPIO5"},
    {name: "0x26", displayName:"(SPI) SPIA_PICO=GPIO16 , SPIA_POCI=GPIO1 , SPIA_CLK=GPIO3 , SPIA_PTE=GPIO0"},
    {name: "0x66", displayName:"(SPI) SPIA_PICO=GPIO16 , SPIA_POCI=GPIO13 , SPIA_CLK=GPIO12 , SPIA_PTE=GPIO24"},
    {name: "0x07", displayName:"(I2C) SDAA=GPIO0 , SCLA=GPIO1"},
    {name: "0x27", displayName:"(I2C) SDAA=GPIO32 , SCLA=GPIO33"},
    {name: "0x47", displayName:"(I2C) SDAA=GPIO5 , SCLA=GPIO4"},
    {name: "0x0A", displayName:"(SECURE FLASH) Flash-Entry-Address=0x00080000 , CPU1 Bank 0 , Sector 0"},
    {name: "0x2A", displayName:"(SECURE FLASH) Flash-Entry-Address=0x00088000 , CPU1 Bank 0 , Sector 32"}
]

exports={
    f28e12x_boot : f28e12x_boot
};