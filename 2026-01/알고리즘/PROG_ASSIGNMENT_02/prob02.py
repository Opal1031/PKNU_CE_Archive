import os

# 주소록 파일을 읽어와 리스트로 반환하는 함수
def ReadAddressFile(file_path):
	loaded_people = []

	with open(file_path, "r", encoding = "utf-8") as f:
		for raw_line in f:
			line = raw_line.strip()

			# '|' 구분자로 필드를 분리
			fields = [field.strip() for field in line.split("|")]

			person = {
				"name": fields[0],
				"company": fields[1],
				"address": fields[2],
				"zipcode": fields[3],
				"phone": fields[4],
				"email": fields[5],
			}
			
			loaded_people.append(person)

	return loaded_people

# 옵션 기준 정렬 (파이썬 표준 정렬)
def SortPeople(people, option):
	col = option.lstrip("-")

	people.sort(key = lambda person: person[col].lower())

# 주소록 출력
def PrintAddressBook(people):
	for person in people:
		print(person["name"])
		print(f"\tCompany: {person['company']}")
		print(f"\tAddress: {person['address']}")
		print(f"\tZipcode: {person['zipcode']}")
		print(f"\tPhones: {person['phone']}")
		print(f"\tEmail: {person['email']}")
		print()

address_book = []

# 명령어 처리
while True:
	command_line = input("$ ").strip()

	parts = command_line.split()
	command = parts[0].lower()

	if (command == "exit"):
		break

	elif (command == "read"):
		file_name = " ".join(parts[1:])
		
		base_dir = os.path.dirname(os.path.abspath(__file__))
		file_path = os.path.join(base_dir, file_name)
		
		address_book = ReadAddressFile(file_path)

	elif (command == "sort"):
		option = parts[1].lower()
		SortPeople(address_book, option)

	elif (command == "print"):
		PrintAddressBook(address_book)