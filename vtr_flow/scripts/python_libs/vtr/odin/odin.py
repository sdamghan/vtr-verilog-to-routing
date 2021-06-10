"""
    Module to run ODIN II with its various arguments
"""
import shutil
from collections import OrderedDict
from pathlib import Path
import xml.etree.ElementTree as ET
from vtr import file_replace, determine_memory_addr_width, verify_file, CommandRunner, paths

# initializing the raw odin config file
def init_config_file (
    odin_config_full_path,
    circuit_list,
    architecture_file,
    output_netlist,
    memory_addr_width,
    min_hard_mult_size,
    min_hard_adder_size,
):
    # Update the config file
    file_replace(
        odin_config_full_path,
        {
            "YYY": architecture_file,
            "ZZZ": output_netlist,
            "PPP": memory_addr_width,
            "MMM": min_hard_mult_size,
            "AAA": min_hard_adder_size,
        },
    )


    # loading the given config file
    config_file = ET.parse(odin_config_full_path)
    root = config_file.getroot()

    # based on the base condfig file
    verilog_files_tag = root.find("verilog_files")
    #remove the template line XXX, verilog_files_tag [0] is a comment 
    verilog_files_tag.remove(verilog_files_tag[0])
    for circuit in circuit_list:
        verilog_file = ET.SubElement(verilog_files_tag, "verilog_file")
        verilog_file.tail = "\n\n\t" if (circuit == circuit_list[-1]) else "\n\n\t\t"
        verilog_file.text = circuit
        
    # update the config file with new values
    config_file.write(odin_config_full_path)


# pylint: disable=too-many-arguments, too-many-locals
def run(
    architecture_file,
    circuit_file,
    include_files,
    output_netlist,
    command_runner=CommandRunner(),
    temp_dir=Path("."),
    odin_args="--adder_type default",
    log_filename="odin.out",
    odin_exec=None,
    odin_config=None,
    min_hard_mult_size=3,
    min_hard_adder_size=1,
):
    """
    Runs ODIN II on the specified architecture file and circuit file

    .. note :: Usage: vtr.odin.run(<architecture_file>,<circuit_file>,<output_netlist>,[OPTIONS])

    Arguments
    =========
        architecture_file :
            Architecture file to target

        circuit_file :
            Circuit file to optimize

        output_netlist :
            File name to output the resulting circuit to

    Other Parameters
    ----------------
        command_runner :
            A CommandRunner object used to run system commands

        temp_dir :
            Directory to run in (created if non-existent)

        odin_args:
            A dictionary of keyword arguments to pass on to ODIN II

        log_filename :
            File to log result to

        odin_exec:
            ODIN II executable to be run

        odin_config:
            The ODIN II configuration file

        min_hard_mult_size :
            Tells ODIN II the minimum multiplier size that should be implemented using
            hard multiplier (if available)

        min_hard_adder_size :
            Tells ODIN II the minimum adder size that should be implemented
            using hard adder (if available).

    """
    temp_dir = Path(temp_dir) if not isinstance(temp_dir, Path) else temp_dir
    temp_dir.mkdir(parents=True, exist_ok=True)

    if odin_args is None:
        odin_args = OrderedDict()

    # Verify that files are Paths or convert them to Paths and check that they exist
    architecture_file = verify_file(architecture_file, "Architecture")
    circuit_file = verify_file(circuit_file, "Circuit")
    output_netlist = verify_file(output_netlist, "Output netlist", False)

    if odin_exec is None:
        odin_exec = str(paths.odin_exe_path)

    if odin_config is None:
        odin_base_config = str(paths.odin_cfg_path)
    else:
        odin_base_config = str(Path(odin_config).resolve())

    # Copy the config file
    odin_config = "odin_config.xml"
    odin_config_full_path = str(temp_dir / odin_config)
    shutil.copyfile(odin_base_config, odin_config_full_path)


    circuit_list = []
    if include_files:
        # Extract includes path 
        for include in include_files:
            include_paths = str(include).split(" ")
            for include_path in include_paths:
                include_file = verify_file(include_path, "Circuit")
                circuit_list.append(include_file.name)            
            
    # append the main circuit design as the last one
    circuit_list.append(circuit_file.name)

    init_config_file(
        odin_config_full_path,
        circuit_list,
        architecture_file.name,
        output_netlist.name,
        determine_memory_addr_width(str(architecture_file)),
        min_hard_mult_size,
        min_hard_adder_size,
    )
    cmd = [odin_exec]
    use_odin_simulation = False

    if "use_odin_simulation" in odin_args:
        use_odin_simulation = True
        del odin_args["use_odin_simulation"]

    for arg, value in odin_args.items():
        if isinstance(value, bool) and value:
            cmd += ["--" + arg]
        elif isinstance(value, (str, int, float)):
            cmd += ["--" + arg, str(value)]
        else:
            pass

    cmd += ["-U0"]

    if "disable_odin_xml" in odin_args:
        del odin_args["disable_odin_xml"]
        cmd += [
            "-a",
            architecture_file.name,
            "-V",
            circuit_file.name,
            "-o",
            output_netlist.name,
        ]
    else:
        cmd += ["-c", odin_config]

    command_runner.run_system_command(
        cmd, temp_dir=temp_dir, log_filename=log_filename, indent_depth=1
    )

    if use_odin_simulation:
        sim_dir = temp_dir / "simulation_init"
        sim_dir.mkdir()
        cmd = [
            odin_exec,
            "-b",
            output_netlist.name,
            "-a",
            architecture_file.name,
            "-sim_dir",
            str(sim_dir),
            "-g",
            "100",
            "--best_coverage",
            "-U0",
        ]
        command_runner.run_system_command(
            cmd,
            temp_dir=temp_dir,
            log_filename="sim_produce_vector.out",
            indent_depth=1,
        )


# pylint: enable=too-many-arguments, too-many-locals
