# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\miker\Documents\My Libraries\Code_Repo\PSoC_Grbl\PSoC_Grbl.cydsn\PSoC_Grbl.cyprj
# Date: Mon, 02 Jul 2018 15:15:22 GMT
#set_units -time ns
create_clock -name {Clock_LCD_Update(routed)} -period 125000000 -waveform {0 62500000} [list [get_pins {ClockBlock/dclk_5}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_clock -name {CyBUS_CLK(fixed-function)} -period 41.666666666666664 -waveform {0 20.8333333333333} [get_pins {ClockBlock/clk_bus_glb_ff}]
create_generated_clock -name {PWM_Clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 240001 480001} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {Clock_Lim_DB} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2400001 4800001} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {Clock_Sw_DB} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2400001 4800001} [list [get_pins {ClockBlock/dclk_glb_4}]]
create_generated_clock -name {Clock_LCD_Update} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3000001 6000001} [list [get_pins {ClockBlock/dclk_glb_5}]]
create_clock -name {CyScBoostClk} -period 83.333333333333329 -waveform {0 41.6666666666667} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 21 41} -nominal_period 833.33333333333326 [list [get_pins {ClockBlock/dclk_glb_0}]]
create_clock -name {Clock_1(fixed-function)} -period 833.33333333333326 -waveform {0 41.6666666666667} -nominal_period 833.33333333333326 [get_pins {ClockBlock/dclk_glb_ff_0}]
create_generated_clock -name {Clock_Step_Pulse} -source [get_pins {ClockBlock/clk_sync}] -edges {1 97 193} [list [get_pins {ClockBlock/dclk_glb_1}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for C:\Users\miker\Documents\My Libraries\Code_Repo\PSoC_Grbl\PSoC_Grbl.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\miker\Documents\My Libraries\Code_Repo\PSoC_Grbl\PSoC_Grbl.cydsn\PSoC_Grbl.cyprj
# Date: Mon, 02 Jul 2018 15:15:11 GMT
