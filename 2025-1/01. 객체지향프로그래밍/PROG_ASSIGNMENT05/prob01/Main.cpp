#include "EventScheduler.h"

void process_command(EventScheduler scheduler) { 
	string command, event_type, date_string, content, keyword;

	while (1) {
		cout << "$ ";
		cin >> command;

		if (command == "add") {
			cin >> event_type;
			cin >> date_string;
			getline(cin, content);
			scheduler.add_event(event_type, date_string, content);
		}

		// find
		else if (command == "find") {
			try {
				cin >> date_string;
				int idx = date_string.find_first_of("-");
				if (idx > 0) {
					Date between_d1(date_string.substr(0, idx));
					Date between_d2(date_string.substr(idx + 1));
					scheduler.show_relevant_events_between(between_d1, between_d2);
				}

				else {
					Date d(date_string);
					scheduler.show_relevant_events(d);
				}
			}

			catch (std::invalid_argument const& ex) {
				cout << "Invalid Date String!!" << ex.what() << "\n";
			}
		}

		else if (command == "search") {
			getline(cin, keyword);
			scheduler.search_events(keyword);
		}

		else if (command == "list") {
			scheduler.show_all_events();
		}

		else if (command == "delete") {
			int id;
			cin >> id;
			scheduler.delete_event(id);
		}

		// save
		else if (command == "save") {
			string filename;
			cin >> filename;
			scheduler.save_events_file(filename);
		}

		else if (command == "exit") {
			break;
		}
	}
}

int main() {
	EventScheduler scheduler;
	scheduler.load_data_file("events.txt");
	process_command(scheduler);

	return 0;
}