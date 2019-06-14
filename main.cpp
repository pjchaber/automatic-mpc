/*
 * This file is part of AutoMATiC.
 * AutoMATiC -- Automatic code generation based on the MATLAB and 
 * C languages.
 * 
 * Copytight (C) 2018-2019 by Patryk Chaber. Developed within the 
 * Warsaw University of Technology, Institute of Control and 
 * Computation Engineering under supervision of Maciej Lawrynczuk. 
 * All rights reserved.
 * 
 * AutoMATiC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * AutoMATiC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with AutoMATiC.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <sstream>
//#include <unistd.h> // Linux

#include <windows.h> // Windows
#include "XGetopt.h" // Windowsowy GetOpt
#include <tchar.h> // Windows 

#include <algorithm>
#include <cstring>

#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

#define BLOCK_OPEN "#MPC_BEGIN"
#define BLOCK_CLOSE "#MPC_END"

// #define BLOCK_INCLUDE "#MPC_INCLUDE"

#define PROFILER_BEGIN "#MPC_PROFILER_BEGIN"
#define PROFILER_COUNT "#MPC_PROFILER_COUNT"
#define PROFILER_END "#MPC_PROFILER_END"
#define PROFILER_PRINT "#MPC_PROFILER_PRINT"

#define TEMP_FILE "C:\\AutoMATiC_Temp\\tmp.c"

#define  PATHBUFSIZE 1000
#define  BUFSIZE 10000

using namespace std;

int main (int argc, TCHAR *argv[]){
	int c;
	
	string input_file_name = "";	// name of file to crosscompile
	string output_file_name = "";	// name of crossompiled file
	string m_libraries_path = "";	// path of MATLAB libraries
	string c_libraries_path = "";	// path of MATLAB libraries
	string simulate_function = "sim_const";  // name of function used to simulate
	
	bool profiler = false;			// do we use profiler?
	bool simulation = false;
	bool software_simulation = false;
	bool hardware_simulation = false;
	bool verbose = false;
	bool interrupt = false;
    bool takeyourtime = false;
    bool nodelay = false;
    bool controldelay = false;

	long iteration_time = 100;	// time of one iteration (needed for one of the usage of crosscompiler)
	long max_time = -1;
	cout << "AutoMATiC transcompiler by Patryk Chaber (2018). Version 0.1" << endl;

	while ((c = getopt (argc, argv, _T("Ivs:h:pt:T:i:o:l:L:dDc"))) != EOF){
		switch (c){
			case _T('i'): // input name
				input_file_name = optarg;
				break;
			case _T('I'): // interrupt mode
				interrupt = true;
				break;
			case _T('v'): // verbose mode
				verbose = true;
				break;
			case _T('p'): // use profiler
				profiler = true;
				break;
            case _T('d'): // ignore timeout conditions
                takeyourtime = true;
                break;
            case _T('c'): // enforce delay for control application
                controldelay = true;
                break;
            case _T('D'): // do not wait for another iteration
                nodelay = true;
                break;
			case _T('s'): // enable software simulation mode
				simulation = true;
				software_simulation = true;
				hardware_simulation = false;
				simulate_function = optarg;
				break;
			case _T('h'): // enable hardware simulation mode
				simulation = true;
				software_simulation = false;
				hardware_simulation = true;
				simulate_function = optarg;
				break;
			case _T('t'): // iteration time
				iteration_time = atoi(optarg);
				break;
			case _T('T'): // timeout time
				max_time = atoi(optarg);
				break;
			case _T('o'): // output name
				output_file_name = optarg;
				break;
			case _T('l'): // output name
				m_libraries_path = optarg;
				break;
			case _T('L'): // output name
				c_libraries_path = optarg;
				break;
			case _T('?'): // error interpreting options
				cout << "[EE] Bad arguments." << endl;
				return 1;
			default:
				break;
		}
	}

	if(input_file_name.empty()){
		cout << "[EE] No input file given. " << endl;
		return 1;
	} else {
		cout << "[II] Input file: " << input_file_name << endl;	    // logs
	}
	if(output_file_name.empty()){
		cout << "[EE] No output file given. " << endl;
		return 1;
	} else {
		cout << "[II] Output file: " << output_file_name << endl;	// logs
	}
	if(m_libraries_path.empty()){
		m_libraries_path = "./Libs/MATLAB/";
	}
    char resolved_path[PATHBUFSIZE]; 
    TCHAR** lppPart={NULL};  // Windows way
    GetFullPathName(m_libraries_path.c_str(),PATHBUFSIZE,resolved_path,lppPart); // Windows way
    //realpath(m_libraries_path.c_str(), resolved_path); 
    m_libraries_path = resolved_path;
	cout << "[II] MATLAB libraries path set to " << m_libraries_path << endl;
	if(c_libraries_path.empty()){
		c_libraries_path = "./Libs/C/";
	}

    GetFullPathName(c_libraries_path.c_str(),PATHBUFSIZE,resolved_path,lppPart); // Windows way
    //realpath(c_libraries_path.c_str(), resolved_path); // Linux way
    c_libraries_path = resolved_path;
	cout << "[II] C libraries path set to " << c_libraries_path << endl;
    cout << "[II] Creating set of defines..." << flush;
	string defines_filename = c_libraries_path+"/defines.h";
	ofstream 	defines_file(defines_filename.c_str());						// open output file as output stream
	defines_file << "#ifndef __DEFINES_H__" << endl << "#define __DEFINES_H__" << endl;
	if(verbose)					defines_file << "#define VERBOSE" << endl;
	if(interrupt)				defines_file << "#define MPC_INTERRUPT" << endl;
	if(simulation)				defines_file << "#define SIMULATION" << endl;
	if(simulation)				defines_file << "#define SIMULATE_FUNCTION " << simulate_function << endl;
	if(hardware_simulation)		defines_file << "#define HARDWARE_SIMULATION" << endl;
	if(software_simulation)		defines_file << "#define SOFTWARE_SIMULATION" << endl;
    if(nodelay)                 defines_file << "#define NO_DELAY" << endl;
    if(controldelay)            defines_file << "#define CONTROL_DELAY" << endl;
    if(takeyourtime)            defines_file << "#define TAKE_YOUR_TIME" << endl;
	if(max_time >= 0)			defines_file << "#define MAX_TIME " << max_time << endl;
	if(!interrupt)				defines_file << "#define ITERATION_TIME " << iteration_time << endl;
	defines_file << "#endif" << endl;
	cout << "OK" << endl;
    string tmp_input_file_name = input_file_name;                           // copy input file name to tmpe input file name
    if(tmp_input_file_name.find_last_of("/") != string::npos){
		replace(tmp_input_file_name.begin()+tmp_input_file_name.find_last_of("/"),tmp_input_file_name.end(),'.','_');
	} else {
		replace(tmp_input_file_name.begin(),tmp_input_file_name.end(),'.','_');
	}
    // replace(tmp_input_file_name.begin(),tmp_input_file_name.end(),'.','_'); // replace all the dots to underscores (MATLAB doesn't like dots since filename is at the same time a function name)
    // tmp_input_file_name.append("_tmp.m");                                   // add to input file name the _tmp.m ending
    cout << "[II] Temporary input file: " << tmp_input_file_name << "###_tmp.m" << endl;   // logs
    string base_tmp_input_file_name = tmp_input_file_name;
    
    cout << "[II] Opening input and output files..." << flush;
    ifstream     input_file(input_file_name.c_str());                       // open input file as input stream
    ofstream    output_file(output_file_name.c_str());                      // open output file as output stream
    ifstream     temp_file;                                                 // open input file as input stream
    ofstream tmp_input_file;                                                // prepare to open tmp input file as output stream
    cout << "OK" << endl;

    cout << "[II] MATLAB engine initialisation..." << flush;
    Engine *ep;
    char buffer_with_prompt[BUFSIZE+1+3]={0};
    char * buffer = buffer_with_prompt;
    if (!(ep = engOpen("matlab -nosplash -nodesktop -nodisplay"))) {
        cout << "[EE] Can't start MATLAB engine" << endl;
        return -1;
    } cout << "OK" << endl;

    engEvalString(ep, "clear all;");
    TCHAR pBuf[PATHBUFSIZE];
    DWORD bytes = GetCurrentDirectory(PATHBUFSIZE, pBuf);
    if(bytes == 0)  return -1;
    cout << "[II] Current working directory (SHELL) : " << pBuf << endl;

    string cd_destination = string(pBuf);
    ofstream clear_temp_file(TEMP_FILE,ios_base::out);
    clear_temp_file.close();

    string cd_command = "cd('"+cd_destination+"');";
    engEvalString(ep, cd_command.c_str());

    engOutputBuffer(ep, buffer_with_prompt, BUFSIZE);
    engEvalString(ep, "disp(pwd)");
    cout << "[II] Current working directory (MATLAB): " << buffer_with_prompt << flush; // buffer contains \n

    cout << "[II] Adding MATLAB library paths..." << flush;
    string library_path = m_libraries_path;
    string addpath_command = "addpath('" + library_path + "');";
    engEvalString(ep, addpath_command.c_str());
    addpath_command = "addpath(cd(cd('./')));";
    engEvalString(ep, addpath_command.c_str());
    cout << "OK" << endl;

    // Linux Style
    // output_file << "#include \""<< c_libraries_path << "/defines.h\"" << endl;
    // if(profiler) output_file << "#include \""<< c_libraries_path << "/profiler.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "/mpctools.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "/simulated_signals.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "/default_functions.h\"" << endl;
    // Windows Style
    output_file << "#include \""<< c_libraries_path << "defines.h\"" << endl;
    if(profiler) output_file << "#include \""<< c_libraries_path << "profiler.h\"" << endl;
    output_file << "#include \""<< c_libraries_path << "mpctools.h\"" << endl;
    output_file << "#include \""<< c_libraries_path << "simulated_signals.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "default_functions.h\"" << endl;
    output_file << "#include \""<< c_libraries_path << "matrix_cal.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "mat_lib.h\"" << endl;
    output_file << "#include \""<< c_libraries_path << "allocation_nr.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "qp.h\"" << endl;
    output_file << "#include \""<< "osqp.h\"" << endl;
    output_file << "#include \""<< "util.h\"" << endl;

    // Porzucone ze wzgledu na uzycie jezyka polskiego
    // output_file << "#include \""<< c_libraries_path << "obl_macierzowe.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "mat_lib.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "alokacja_nr.h\"" << endl;
    // output_file << "#include \""<< c_libraries_path << "pk.h\"" << endl;
    
	string line;
    bool block_open = false;
    long int block_counter = 0;
	while (getline(input_file, line)){
		istringstream iss(line);
		string word;
		if(!(iss >> word)) {
			word = "";
		} // if there is no word

		if(!block_open && word.compare(BLOCK_OPEN)==0){ // if there is a block opening keyword
            tmp_input_file_name = base_tmp_input_file_name;
            tmp_input_file_name.append(to_string(block_counter++));  
            tmp_input_file_name.append("_tmp.m");                                   // add to input file name the _tmp.m ending
            cout << "[II] Opening temporary file: " << tmp_input_file_name << "..." << flush;
			tmp_input_file.open(tmp_input_file_name.c_str(), ios_base::out);
			while(!tmp_input_file.is_open());
            cout << "OK" << endl;
			block_open = true;
		} else if (block_open && word.compare(BLOCK_CLOSE)==0){ // if there is a block closing keyword
            block_open = false;
            cout << "[II] Closing temporary file: " << tmp_input_file_name << "..." << flush;
            tmp_input_file.close();
            while(tmp_input_file.is_open());
            cout << "OK" << endl;
            cout << "[II] Setting global flag MPC_CROSSCOMPILER..." << flush;
            string global_command = "global MPC_CROSSCOMPILER; MPC_CROSSCOMPILER = 1;";
            engEvalString(ep, global_command.c_str());
            cout << "OK" << endl;
            cout << "[II] Running temporary file: " << tmp_input_file_name << "..." << flush;
            string run_command = "run ./" + tmp_input_file_name + ";";
            memset(buffer_with_prompt,0,BUFSIZE+1);
            engEvalString(ep, run_command.c_str());
            cout << "OK" << endl;
            cout << buffer_with_prompt << endl;
            cout << "[II] Opening temporary file: " << TEMP_FILE << "..." << flush;
            temp_file.open(TEMP_FILE);
            while(!temp_file.is_open());
            cout << "OK" << endl;
            // stringstream temp_file_buf;
            // temp_file_buf << temp_file.rdbuf(); 
            cout << "[II] Saving temporary file: " << TEMP_FILE << "..." << flush;
            output_file << temp_file.rdbuf();
            output_file.clear();
            temp_file.close();
            while(temp_file.is_open());
            cout << "OK" << endl;
		} else if(block_open){ // if the block is opened - we are reading it line by line
			tmp_input_file << line << endl;
		// } else if(word.compare(BLOCK_INCLUDE)==0){
		// 	iss >> word;
		// 	string run_command = "run ./" + word.substr(1,word.size()-4) + ";";
		// 	memset(buffer_with_prompt,0,BUFSIZE+1);
		// 	engEvalString(ep, run_command.c_str());
		// 	output_file << buffer;
		} else if(word.compare(PROFILER_BEGIN)==0){
			iss >> word;
			int id = atoi(word.c_str());
			string profiler_name = "";
			if(profiler) {
				// output_file << "profiler_start("<<id<<");" << endl;
				while(iss >> word){
					if(!profiler_name.empty()) 
						profiler_name.append(" ");
					profiler_name.append(word);
				}
				output_file << "profiler_start("<<id<<",\""<<profiler_name<<"\");" << endl;
			}
		} else if(word.compare(PROFILER_COUNT)==0){
			iss >> word;
			int id = atoi(word.c_str());
			string profiler_name = "";
			if(profiler) {
				// output_file << "profiler_count("<<id<<");" << endl;				
				while(iss >> word){
					if(!profiler_name.empty()) 
						profiler_name.append(" ");
					profiler_name.append(word);
				}
				output_file << "profiler_count("<<id<<",\""<<profiler_name<<"\");" << endl;
			}
        } else if(word.compare(PROFILER_END)==0){
            iss >> word;
            int id = atoi(word.c_str());
            if(profiler) {
                output_file << "profiler_end("<<id<<");" << endl;
            }
        } else if(word.compare(PROFILER_PRINT)==0){
            if(profiler) {
                output_file << "profiler_print();" << endl;
            }
		} else {
			output_file << line << endl;
		}

	}
	input_file.close();
	engEvalString(ep, "clear MPC_CROSSCOMPILER;");
	//engClose(ep);

	cout << "[II] End of cross compilation." << endl << endl;

	return 0;
}

