#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>

#define BUF_SIZE 128

using std::cout;
using std::endl;
using std::ifstream;

char space_variable[BUF_SIZE];
int count_prog = 0, count_cook = 0, count_esot = 0, count_disk = 0;

char *space_f(int len_space);

class product {
    char barcode[BUF_SIZE];
    char name[BUF_SIZE];
    int price;
 public:
    void set_barcode(char *test) { strcpy(barcode, test); }
    void set_name(char *test_n) { strcpy(name, test_n); }
    void set_price(int test_price) { price = test_price; }
    char *get_barcode() { return barcode; }
    char *get_name() { return name; }
    int get_price() { return price; }
};

class book : public product {
    int pages;
 public:
    void set_pages(int test_pages) { pages = test_pages; }
    int get_pages() { return pages; }
};

class program_book : public book {
    char language[BUF_SIZE];
 public:
    void set_param(char *name, char *barcode, int price, int pages, char *test_language) {
        set_name(name);
        set_barcode(barcode);
        set_price(price);
        set_pages(pages);
        strcpy(language, test_language);
    }
    char *get_param() { return language; }
};

class cookery_book : public book {
    char ingredient[BUF_SIZE];
 public:
    void set_ingredient(char *test_ingredient) { strcpy(ingredient, test_ingredient); }
    void set_param(char *name, char *barcode, int price, int pages, char *test_ingredient) { 
        set_name(name);
        set_barcode(barcode);
        set_price(price);
        set_pages(pages);
        strcpy(ingredient, test_ingredient);
    }
    char *get_param() { return ingredient; }
};

class esoterics_book : public book {
    int minimum_age;
 public:
    void set_minimum_age(int test_minimum_age) { minimum_age = test_minimum_age; }
    void set_param(char *name, char *barcode, int price, int pages, int test_minimum_age) { 
        set_name(name);
        set_barcode(barcode);
        set_price(price);
        set_pages(pages);
        minimum_age = test_minimum_age;
    }
    int get_param() { return minimum_age; }
};

class disk : public product {
	char type_disk[BUF_SIZE];
	char content[BUF_SIZE];
 public:
	char *get_type_disk() { return type_disk; }
	char *get_content() { return content; }
	void set_param(char *name, char *barcode, int price, char *type, char *content_t) { 
		set_name(name);
		set_barcode(barcode);
		set_price(price);
		strcpy(type_disk, type);
		strcpy(content, content_t);
	}
};

struct object_struct {
    program_book array_prog[20];
    cookery_book array_cook[20];
    esoterics_book array_esot[20];
    disk array_disk[20];
};

void output(int indent_a, int indent_b, bool choice, object_struct object, int count, int var) {
    char str[BUF_SIZE] = "|     |", str1[BUF_SIZE] = "|";
    if (choice == false)
        strcpy(str, str1);
    cout << space_f(indent_a) << str;
    cout << space_f(indent_b) << str1 << endl;
    cout << space_f(indent_a) << str;
    if (var == 0) {
        cout << space_f(indent_b) << "|--" << object.array_prog[count].get_name() << " | "
             << object.array_prog[count].get_param() << " | " 
             << object.array_prog[count].get_barcode() << "   | "
             << object.array_prog[count].get_pages() << " | "
             << object.array_prog[count].get_price() << " |" << endl;
    } else if (var == 1) {
        cout << space_f(indent_b) << "|--" << object.array_cook[count].get_name() << " | "
             << object.array_cook[count].get_param() << " | " 
             << object.array_cook[count].get_barcode() << " | "
             << object.array_cook[count].get_pages() << " | "
             << object.array_cook[count].get_price() << " |" << endl;
    } else if (var == 2) {
        cout << space_f(indent_b) << "|--" << object.array_esot[count].get_name() << " | "
             << object.array_esot[count].get_param() << " | " 
             << object.array_esot[count].get_barcode() << " | "
             << object.array_esot[count].get_pages() << " | "
             << object.array_esot[count].get_price() << " |" << endl;
    }

}

void print_disk_data(disk *OBJ3) {
	cout << space_f(13) << "|--" << "Диски:" << endl;
		for (int i = 0; i < count_disk; ++i) {
			cout << space_f(20) << "|" << endl;
			cout << space_f(20) << "|--" << OBJ3[i].get_name() << " | " << OBJ3[i].get_type_disk() << " | " 
					<< OBJ3[i].get_barcode() << " | " << OBJ3[i].get_content() << " | " << OBJ3[i].get_price() << endl;
		}
}

void inform_about_branch(int indent_a, int indent_b, char *title_str, char *data_str) {
	cout << space_f(indent_a) << "|     |" << "\n";
	cout << space_f(indent_a) << "|     |--" << title_str << endl;
	cout << space_f(indent_a) << "|     |";
	cout << space_f(indent_b) << "|" << endl;
	cout << space_f(indent_a) << "|     |";
	cout << space_f(indent_b) << "|  " << "Название | " << data_str 
		<< "Штрих-код | " << "Кол-во страниц | " << "Цена |" << endl;
}

void create_tree(object_struct base_object) {

	cout << "Каталог товаров:" << "\n" << space_f(13) << "|" << "\n"
			<< space_f(13) << "|--" << "Книги:" << endl;
	char str_title[BUF_SIZE] = {"По программированию:"};
	char str_data[BUF_SIZE] = {"Язык програм | "};
	inform_about_branch(13, 20, str_title, str_data);
	for (int i = 0; i < count_prog; ++i) {
		if (count_cook == 0 && count_esot == 0) {
            output(13, 20, false, base_object, i, 0);
		} else {
            output(13, 20, true, base_object, i, 0);
		}
	}
	if (count_cook == 0) {
		if (count_esot == 0)
			print_disk_data(base_object.array_disk);
	} else {
		strcpy(str_title, "По кулинарии:");
		strcpy(str_data, "Ингридиенты | ");
		inform_about_branch(13,  13, str_title, str_data);
		for (int i = 0; i < count_cook; ++i) {
			if (count_esot == 0) {
				output(13, 19, false, base_object, i, 1);
            } else {
                output(13, 13, true, base_object, i, 1);
            }
        }
    }
    if (count_esot == 0) {
        print_disk_data(base_object.array_disk);
    } else {
        strcpy(str_title, "По эзотерике:");
        strcpy(str_data, "Возраст | ");
        inform_about_branch(13,  13, str_title, str_data);
        for (int i = 0; i < count_esot; ++i)
            output(13, 19, false, base_object, i, 2);
        print_disk_data(base_object.array_disk);
    }
}

int main() {
    int count = 0;
    char buff[BUF_SIZE][BUF_SIZE];
    ifstream input_file("input.txt");
    object_struct base_object;

    while (input_file.good()) {
        input_file.getline(buff[count], 50);
        ++count;
        if(count == 10) {
            if (strcmp(buff[4],"NONE")) {
                base_object.array_prog[count_prog].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), buff[4]);
                ++count_prog;
            }
            if (strcmp(buff[5],"NONE")) {
                base_object.array_cook[count_cook].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), buff[5]);
                ++count_cook;
            }
            if (strcmp(buff[6],"NONE")) {
                base_object.array_esot[count_esot].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), atoi(buff[6]));
                ++count_esot;
            }
            if (strcmp(buff[7],"NONE")) {
                base_object.array_disk[count_disk].set_param(buff[0], buff[1], atoi(buff[2]), buff[7], buff[8]);
                ++count_disk;
            }
            count = 0;
        }
    }
    input_file.close();
    create_tree(base_object);
    return 0;
}

char *space_f(int len_space) {
    strcpy(space_variable, "");
    for (int i = 0; i < len_space; ++i)
        strcat(space_variable, " ");
    return space_variable;
}
