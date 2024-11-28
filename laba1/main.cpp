#include "nps.h"
#include "pipeline.h"
#include "network.h"
#include "utils.h"
#include <chrono>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void backToMenu() {
	string k;
	cout << endl << "Press 0 to return to menu" << endl;
	getline(cin, k);
	while (k != "0") {
		cout << "Press 0 to return to menu" << endl;
		getline(cin, k);
	}
}
void NoOneObject() {
	cout << "No objects found" << endl;
}

int main() {
	string input;
	unordered_map<int,nps> all_nps;
	int idpipes=0;
	int idnps=0;
	int a;
	pipeline pipe;
	string k;
	nps nps;
	unordered_map<int,pipeline> all_pipeline;
	Network network(all_pipeline,all_nps);
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", chrono::system_clock::now());
	ofstream logfile("log_" + time+".txt");
	if (logfile)
		cerr_out.redirect(logfile);
	while(true){
		system("cls");
		cout << "Choose action:" << endl;
		cout << "1. Add pipeline" << endl;
		cout << "2. Add station (CS)" << endl;
		cout << "3. View all objects" << endl;
		cout << "4. Edit pipeline" << endl;
		cout << "5. Edit station (CS)" << endl;
		cout << "6. Save to file" << endl;
		cout << "7. Load from file" << endl;
		cout << "8. Connect stations in network" << endl;
		cout << "9. View network" << endl;
		cout << "10. Topological sort" << endl;
		cout << "0. Exit" << endl;
		getline(cin, input);
		try {
			a = stoi(input);
		}
		catch (invalid_argument e) {
			cout << "Enter correct number" << endl;
			continue;
		}
		switch (a)
		{
		case 1:
			system("cls");
			cin >> pipe;
			all_pipeline[++idpipes] = pipe;
			break;
		case 2:
			system("cls");
			cin >> nps;
			all_nps[++idnps] = nps;
			break;
		case 3:
			system("cls");
			if (all_nps.size() == 0 and all_pipeline.size() == 0)
				NoOneObject();
			else {
				ShowAllPipe(all_pipeline);
				ShowAllNPS(all_nps);
			}
			backToMenu();
			break;
		case 4:
			system("cls");
			if (all_pipeline.size() == 0)
				NoOneObject();
			else
				EditPipe(all_pipeline);
			backToMenu();
			break;
		case 5:
			system("cls");
			if (all_nps.size() == 0)
				NoOneObject();
			else
				EditNPS(all_nps);
			backToMenu();
			break;
		case 6: {
			system("cls");
			cout << "Enter file name:" << endl;
			string filename;
			getline(cin, filename);
			ofstream file(filename+".txt");
			file << idpipes << endl;
			file << idnps << endl;
			PipeToFile(all_pipeline, file);
			NPSToFile(all_nps, file);
			file.close();
			cout << "Objects saved to file" << endl;
			backToMenu();
		}
			break;
		case 7:
		{
			system("cls");
			cout << "Enter file name:" << endl;
			string filename;
			getline(cin, filename);
			ifstream file(filename+".txt");
			if (!file.is_open()) {
				cout << "File not found or access denied" << endl;
				backToMenu();
				continue;
			}
			string input;
			getline(file, input);
			idpipes = stoi(input);
			getline(file, input);
			idnps = stoi(input);
			all_pipeline = PipeFromFile(file);
			all_nps = NPSFromFile(file);
			file.close();
			cout << "Objects loaded from file" << endl;
			backToMenu();
		}
			break;
		case 8:
    		system("cls");
    		network.handleConnect();
   			backToMenu();
  			break;
		case 9:
    		system("cls");
    		network.viewNetwork();
    		backToMenu();
    		break;
		case 10:
    		system("cls");
    		network.viewTopologicalSort();
    		backToMenu();
    		break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Enter correct number" << endl;
		}
	}
}