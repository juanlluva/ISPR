connect -url tcp:127.0.0.1:3121
set bp_50_5_0 [bpadd -ct-input {0} -ct-output {24 25 26 27}]
set bp_50_5_1 [bpadd -ct-input {24 25 26 27} -ct-output {0}]
source C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab2/lab2.sdk/system_wrapper_hw_platform_1/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
loadhw -hw C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab2/lab2.sdk/system_wrapper_hw_platform_1/system.hdf -mem-ranges [list {0x40000000 0xbfffffff}]
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent Zybo 210279787313A"} -index 0
dow C:/Users/JuanLluva/MUIT_LOCAL/ISPR/lab2/lab2.sdk/lab2/Debug/lab2.elf
configparams force-mem-access 0
bpadd -addr &main
