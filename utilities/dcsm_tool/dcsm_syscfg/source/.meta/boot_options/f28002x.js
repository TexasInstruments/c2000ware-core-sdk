let f28002x_boot =[
    {name: "0x00", displayName:"(PARALLEL) D0-D7=GPIO(28,1-7) , MCU-Control=GPIO16 , Host-Control=GPIO29"},
    {name: "0x20", displayName:"(PARALLEL) D0-D7=GPIO(0-7) , MCU-Control=GPIO16 , Host-Control=GPIO11"},
    {name: "0x01", displayName:"(SCI) SCIATX=GPIO29 , SCIARX=GPIO28"},
    {name: "0x21", displayName:"(SCI) SCIATX=GPIO16 , SCIARX=GPIO17"},
    {name: "0x41", displayName:"(SCI) SCIATX=GPIO8 , SCIARX=GPIO9"},
    {name: "0x61", displayName:"(SCI) SCIATX=GPIO2 , SCIARX=GPIO3"},
    {name: "0x81", displayName:"(SCI) SCIATX=GPIO16 , SCIARX=GPIO3"},
    {name: "0x02", displayName:"(CAN) CANTXA=GPIO4 , CANRXA=GPIO5"},
    {name: "0x22", displayName:"(CAN) CANTXA=GPIO32 , CANRXA=GPIO33"},
    {name: "0x42", displayName:"(CAN) CANTXA=GPIO2 , CANRXA=GPIO3"},
    {name: "0x03", displayName:"(FLASH) Flash-Entry-Address=0x00080000 , CPU1 Bank 0 , Sector 0"},
    {name: "0x23", displayName:"(FLASH) Flash-Entry-Address=0x00084000 , CPU1 Bank 0 , Sector 4"},
    {name: "0x43", displayName:"(FLASH) Flash-Entry-Address=0x00088000 , CPU1 Bank 0 , Sector 8"},
    {name: "0x63", displayName:"(FLASH) Flash-Entry-Address=0x0008EFF0 , CPU1 Bank 0 , Sector 14"},
    {name: "0x04", displayName:"(WAIT) Watchdog is Enabled"},
    {name: "0x24", displayName:"(WAIT) Watchdog is Disabled"},
    {name: "0x05", displayName:"(RAM) RAM-Entry-Point-Address=0x00000000"},
    {name: "0x06", displayName:"(SPI) SPIA_SIMO=GPIO2 , SPIA_SOMI=GPIO1 , SPIA_CLK=GPIO3 , SPIA_STE=GPIO5"},
    {name: "0x26", displayName:"(SPI) SPIA_SIMO=GPIO16 , SPIA_SOMI=GPIO1 , SPIA_CLK=GPIO3 , SPIA_STE=GPIO0"},
    {name: "0x46", displayName:"(SPI) SPIA_SIMO=GPIO8 , SPIA_SOMI=GPIO10 , SPIA_CLK=GPIO9 , SPIA_STE=GPIO11"},
    {name: "0x66", displayName:"(SPI) SPIA_SIMO=GPIO8 , SPIA_SOMI=GPIO17 , SPIA_CLK=GPIO9 , SPIA_STE=GPIO11"},
    {name: "0x07", displayName:"(I2C) SDAA=GPIO32 , SCLA=GPIO33"},
    {name: "0x27", displayName:"(I2C) SDAA=GPIO0 , SCLA=GPIO1"},
    {name: "0x47", displayName:"(I2C) SDAA=GPIO10 , SCLA=GPIO8"}
]

exports={
    f28002x_boot : f28002x_boot
};