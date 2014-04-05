/*
C++ server for web-driven administration with module support.
Copyright (C) 2014  Vladimír Bartošík, Martin Kuzma, Marek Moravčík

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "systemInfo.h"

//variables
const int numberOfItems = 15;
float array [numberOfItems];

const std::string script_start =
		"<script type=\"text/javascript\">"
		"function drawGraph(){"
		"  var canvas = document.getElementById('mycanvas');"
		" "
		"  if (canvas.getContext){"
		""
		"    var ctx = canvas.getContext('2d');"
		""
		"    var pole=[";

const std::string script_end =
		"];"
		"    var shiftGraph = 25;"
		""
		"    ctx.beginPath();"
		"    ctx.moveTo(shiftGraph, 0);"
		"    ctx.lineTo(shiftGraph, canvas.height-1);"
		"    ctx.lineTo(canvas.width, canvas.height-1);"
		"    ctx.lineWidth = 2;"
		"    ctx.stroke();"
		""
		"    ctx.font=\"10px Georgia\";"
		""
		"    for (var i=1;i<6;i++){"
		"	ctx.fillText(i*20, 0, canvas.height-(canvas.height/100)*20*i +8);"
		"    }"
		""
		"    ctx.beginPath();"
		"    ctx.lineWidth = 0.2;"
		"    for (var i=0;i<pole.length;i++){"
		"	ctx.moveTo(canvas.width/pole.length*i+shiftGraph, 0);"
		"	ctx.lineTo(canvas.width/pole.length*i+shiftGraph, canvas.height)"
		"    }"
		""
		"    for (var i=0;i<5;i++){"
		"	ctx.moveTo(shiftGraph, (canvas.height/100*i*20)+1);"
		"	ctx.lineTo(canvas.width, ((canvas.height/100)*20*i)+1)"
		"    }"
		""
		"    ctx.stroke();"
		""
		"    ctx.beginPath();"
		"    ctx.strokeStyle = '#ff0000';"
		"    ctx.lineWidth = 3;"
		""
		"    for (var i=0;i<pole.length;i++){"
		"	ctx.lineTo((canvas.width/pole.length*i)+shiftGraph, canvas.height-(canvas.height/102*pole[i]));"
		"    }"
		"   "
		"    ctx.stroke();"
		" "
		"  } else {"
		"    alert('You need Safari or Firefox 1.5+ to see graph.');"
		"  }"
		"}"
		"</script>"
		"<canvas id=\"mycanvas\" width=\"500\" height=\"300\"></canvas>"
		"<script>"
		"drawGraph();"
		"</script>";

SystemInfo::SystemInfo() {
	name = "System info";
	slug = "systeminfo";
}

SystemInfo::~SystemInfo() {
}

void SystemInfo::init(){
	//initialize array with CPU values
	for (int i=0; i<numberOfItems; i++){
		 array[i]=0;
	}
}

/**
 * reads text file and returns it as std::string
 */
std::string read_text_file(const char* path){
	std::ifstream citanySubor;
	std::string str;
	std::string output;

	citanySubor.open(path);
	if (citanySubor.is_open()) {
		while(!citanySubor.eof()){
			getline(citanySubor, str);//nacitam riadok
			output.append(str);
			output.append("\n");
		}
	}
	else{//ak sa neda otvorit
		return NULL;
	}
	citanySubor.close();//zatvorim subor

	return output;
}

/**
 * returns programs output to console as std::string
 */
std::string get_output_from_stdin(const char* param){
	std::string riadok;
	FILE *pipein_fp;
	char readbuf[20];

	//presmerujem STDIN
	if (( pipein_fp = popen(param, "r")) == NULL){
        return NULL;
	}

	//po znakoch nacitam zo STDIN
	while(fgets(readbuf, 20, pipein_fp));
	riadok.append(readbuf);//lepim do stringu

	//posledny znak je \n tak ho odoberiem a dam do premennej
	riadok = riadok.substr(0, riadok.length()-1);

	//zatvorim presmerovanie
	pclose(pipein_fp);

	return riadok;
}

/**
 * creates std::string of html code which paints graph of CPU usage history
 */
std::string getGraph(){

	std::string vysledok = script_start;
	char pomString [64];

	//posunutie pola
	for (int i=0; i<numberOfItems-1; i++){
		 array[i]=array[i+1];
	}

	//ziskanie dat
	array[numberOfItems-1] = atof(get_output_from_stdin("top -bn 2 -d 0.01 | grep '^Cpu.s.' | tail -n 1 | gawk '{print $2+$4+$6}'").c_str());

	//vytvorenie hodnot a vlepenie ich do stringu
	for (int i=0; i<numberOfItems; i++){
		sprintf(pomString, "%.2f, ", array[i]);
		vysledok.append(pomString);
	}

	//dolepenie konca skriptu a nasledne vypisanie do tela
	vysledok.append(script_end);

	return vysledok;
}

std::string SystemInfo::onRequest(const map<string,string>* query){

	std::string vystup ="";
	char pomString [32];
	std::string text_file;

	WebTabBuilder tabs;

    int CPUcores = 0;//pocet jadier CPU
    std::string CPUModel;
    std::string architektura;
	int MemTotal = 0;//celkova RAM
	std::string verziaJadra;
	std::string verziaGCC;


	//typ procesora
	text_file = read_text_file("/proc/cpuinfo");//nacitam cely subor
	text_file = text_file.substr(text_file.find("model name"));//zacnem vo vybranom riadku
	text_file = text_file.substr(0, text_file.find("\n"));//pojdem len do konca riadku
	CPUModel = text_file.substr(text_file.find(":")+2);//zacnem az po ": "

	//celkova pamat
	text_file = read_text_file("/proc/meminfo");
	text_file = text_file.substr(text_file.find("MemTotal:")+9);
	text_file = text_file.substr(0, text_file.find("\n"));
	MemTotal = atoi(text_file.c_str());

	//pocet jadier
	text_file = read_text_file("/proc/cpuinfo");
	text_file = text_file.substr(text_file.find("cpu cores"));
	text_file = text_file.substr(0, text_file.find("\n"));
	CPUcores = atoi(text_file.substr(text_file.find(":")+2).c_str());

	architektura = get_output_from_stdin("uname -m");
	verziaJadra = get_output_from_stdin("uname -r");
	verziaGCC = get_output_from_stdin("cat /proc/version | grep -o 'gcc.*' | grep -o '[0-9]\\.[0-9]\\.[0-9] '");

	vystup.append("<div><table><tr><td>CPU cores:</td><td>");
	sprintf(pomString, "%d", CPUcores);
	vystup.append(pomString);
	vystup.append("</td></tr><tr><td>CPU model:</td><td>");
	vystup.append(CPUModel);
	vystup.append("</td></tr><tr><td>Architecture:</td><td>");
	vystup.append(architektura);
	vystup.append("</td></tr><tr><td>Total memory:</td><td>");
	sprintf(pomString, "%d", MemTotal);
	vystup.append(pomString);
	vystup.append(" KB</td></tr><tr><td>Core version:</td><td>");
	vystup.append(verziaJadra);
	vystup.append("</td></tr><tr><td>GCC version:</td><td>");
	vystup.append(verziaGCC);
	vystup.append("</td></tr></table></div>");

	tabs.addTab("Info", vystup);
	tabs.addTab("CPU Usage", getGraph() );

	return tabs.build();
}

extern "C"{
	void* createInstance(){
		return (void*)new SystemInfo();
	}
}
