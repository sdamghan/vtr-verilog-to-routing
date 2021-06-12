yosys -import
	
# Read VTR baseline library first.
read_verilog -lib $env(PRIMITIVES); 

read_verilog $env(TCL_CIRCUIT); 
hierarchy -check -auto-top

autoname;
#expose -dff;
procs; 

opt;

fsm;

opt;

memory;

opt;

check;

flatten;

autoname;

write_blif -param -impltf $env(OUTPUT_BLIF_PATH)/$env(TCL_BLIF_NAME);

exit;