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

void output(int indent_a, int indent_b, bool choice, program_book OBJ, cookery_book OBJ1, esoterics_book OBJ2, int var) {
    char str[BUF_SIZE] = "|     |", str1[BUF_SIZE] = "|";
	if (choice == false)
		strcpy(str, str1);
	cout << space_f(indent_a) << str;
	cout << space_f(indent_b) << str1 << endl;
	cout << space_f(indent_a) << str;
	if (var == 0) {
		cout << space_f(indent_b) << "|--" << OBJ.get_name() << " | " << OBJ.get_param() << " | " 
				<< OBJ.get_barcode() << "   | " << OBJ.get_pages() << " | " << OBJ.get_price() << " |" << endl;
	} else if (var == 1) {
		cout << space_f(indent_b) << "|--" << OBJ1.get_name() << " | " << OBJ1.get_param() << " | " 
				<< OBJ1.get_barcode() << " | " << OBJ1.get_pages() << " | " << OBJ1.get_price() << " |" << endl;
	} else if (var == 2) {
		cout << space_f(indent_b) << "|--" << OBJ2.get_name() << " | " << OBJ2.get_param() << " | " 
				<< OBJ2.get_barcode() << " | " << OBJ2.get_pages() << " | " << OBJ2.get_price() << " |" << endl;
	}

}

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
    program_book *object_program;
    program_book array_book_prog[20];
    cookery_book *object_cookery;
    esoterics_book *object_esoterics;
    disk *object_disk;
};

void output_test(int indent_a, int indent_b, bool choice, program_book testing) {
    char str[BUF_SIZE] = "|     |", str1[BUF_SIZE] = "|";
    if (choice == false)
        strcpy(str, str1);
    cout << space_f(indent_a) << str;
    cout << space_f(indent_b) << str1 << endl;
    cout << space_f(indent_a) << str;
    cout << space_f(indent_b) << "|--" << testing.get_name() << " | " << testing.get_param() << " | " 
                << testing.get_barcode() << "   | " << testing.get_pages() << " | " << testing.get_price() << " |" << endl;
    /*if (var == 0) {
        cout << space_f(indent_b) << "|--" << OBJ.get_name() << " | " << OBJ.get_param() << " | " 
                << OBJ.get_barcode() << "   | " << OBJ.get_pages() << " | " << OBJ.get_price() << " |" << endl;
    } else if (var == 1) {
        cout << space_f(indent_b) << "|--" << OBJ1.get_name() << " | " << OBJ1.get_param() << " | " 
                << OBJ1.get_barcode() << " | " << OBJ1.get_pages() << " | " << OBJ1.get_price() << " |" << endl;
    } else if (var == 2) {
        cout << space_f(indent_b) << "|--" << OBJ2.get_name() << " | " << OBJ2.get_param() << " | " 
                << OBJ2.get_barcode() << " | " << OBJ2.get_pages() << " | " << OBJ2.get_price() << " |" << endl;
    }*/

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

void create_tree(program_book *OBJ, cookery_book *OBJ1, esoterics_book *OBJ2, disk *OBJ3, object_struct first) {

    cout << "+++++++++++++++" << first.array_book_prog[count_prog - 2].get_name() << endl;

	cout << "Каталог товаров:" << "\n" << space_f(13) << "|" << "\n"
			<< space_f(13) << "|--" << "Книги:" << endl;
	char str_title[BUF_SIZE] = {"По программированию:"};
	char str_data[BUF_SIZE] = {"Язык програм | "};
	inform_about_branch(13, 20, str_title, str_data);
	for (int i = 0; i < count_prog; ++i) {
		if (count_cook == 0 && count_esot == 0) {
			output(13, 26, false, OBJ[i], OBJ1[i], OBJ2[i], 0);
		} else {
			output(13, 20, true, OBJ[i], OBJ1[i], OBJ2[i], 0);
            output_test(13, 20, true, first.array_book_prog[i]);
		}
	}
	if (count_cook == 0) {
		if (count_esot == 0)
			print_disk_data(OBJ3);
	} else {
		strcpy(str_title, "По кулинарии:");
		strcpy(str_data, "Ингридиенты | ");
		inform_about_branch(13,  13, str_title, str_data);
		for (int i = 0; i < count_cook; ++i) {
			if (count_esot == 0) {
				output(13, 19, false, OBJ[i], OBJ1[i], OBJ2[i], 1);
            } else {
                output(13, 13, true, OBJ[i], OBJ1[i], OBJ2[i], 1);
            }
        }
    }
    if (count_esot == 0) {
        print_disk_data(OBJ3);
    } else {
        strcpy(str_title, "По эзотерике:");
        strcpy(str_data, "Возраст | ");
        inform_about_branch(13,  13, str_title, str_data);
        for (int i = 0; i < count_esot; ++i)
            output(13, 19, false, OBJ[i], OBJ1[i], OBJ2[i], 2);
        print_disk_data(OBJ3);
    }
}

int main() {
    int count = 0;
    char buff[BUF_SIZE][BUF_SIZE];
    ifstream input_file("input.txt");
    object_struct test_array;
    program_book prog_array[20];
    cookery_book cook_array[20];
    esoterics_book esot_array[20];
    disk disk_array[20];
    while (input_file.good()) {
        input_file.getline(buff[count], 50);
        ++count;
        if(count == 10) {
            if (strcmp(buff[4],"NONE")) {
                prog_array[count_prog].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), buff[4]);
                test_array.array_book_prog[count_prog].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), buff[4]);
                ++count_prog;
            }
            if (strcmp(buff[5],"NONE")) {
                cook_array[count_cook].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), buff[5]);
                ++count_cook;
            }
            if (strcmp(buff[6],"NONE")) {
                esot_array[count_esot].set_param(buff[0], buff[1], atoi(buff[2]), atoi(buff[3]), atoi(buff[6]));
                ++count_esot;
            }
            if (strcmp(buff[7],"NONE")) {
                disk_array[count_disk].set_param(buff[0], buff[1], atoi(buff[2]), buff[7], buff[8]);
                ++count_disk;
            }
            count = 0;
        }
    }
    cout << "============== " << test_array.array_book_prog[count_prog - 1].get_name() << endl;
    input_file.close();
    create_tree(prog_array, cook_array, esot_array, disk_array, test_array);
    return 0;
}

char *space_f(int len_space) {
    strcpy(space_variable, "");
    for (int i = 0; i < len_space; ++i)
        strcat(space_variable, " ");
    return space_variable;
}
