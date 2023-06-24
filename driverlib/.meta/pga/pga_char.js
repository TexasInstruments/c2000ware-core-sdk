var SH_F28004x = {
    PGA1     : { GAIN: 3   , ADC_SH_MIN: 160       },       
    PGA2     : { GAIN: 6   , ADC_SH_MIN: 160       },       
    PGA3     : { GAIN: 12   , ADC_SH_MIN: 160       },       
    PGA4     : { GAIN: 24   , ADC_SH_MIN: 200        },       
    PGA5     : { CMP_DIS: 9.2    , CMP_EN: 11.7       },       
    PGA6     : { CMP_DIS: 7.5    , CMP_EN: 10         },   
    PGA7     : { CMP_DIS: 8.0    , CMP_EN: 10.5       },              
}

var SH = {
    F28004x: { ADC_SH_MIN: 160, ADC_SH_MIN_GAIN24: 200 },
}
    
exports = {
    SH: SH,
}