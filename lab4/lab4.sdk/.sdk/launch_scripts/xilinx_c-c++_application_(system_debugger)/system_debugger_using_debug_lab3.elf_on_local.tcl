connect -url tcp:127.0.0.1:3121
source C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab3/lab3.sdk/system_wrapper_hw_platform_1/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
loadhw -hw C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab3/lab3.sdk/system_wrapper_hw_platform_1/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
dow C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab3/lab3.sdk/lab3/Debug/lab3.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
con
