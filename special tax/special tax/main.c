#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct RECORD {
	int id;
	char lname[64];
	char fname[64];
	char email[64];
	struct RECORD* next;
};

//���R�[�h��
int CRecord;
//ID
int id = 1;

//���R�[�h�z��
struct RECORD* new_record;

struct RECORD* head = NULL;
void read_data(FILE* file) {

	fscanf(file, "%d", &CRecord);

	new_record = (struct RECORD*)malloc(sizeof(struct RECORD) * CRecord + 1);
	if (new_record == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	for (int i = 0; i < CRecord; i++) {

		fscanf(file, "%s %s %s", new_record[i].lname, new_record[i].fname, new_record[i].email);

		new_record[i].id = id;
		id++;
		if (i > 0) {
			new_record[i - 1].next = &new_record[i];
		}
	}
	new_record[CRecord - 1].next = NULL;
	head = new_record;
	fclose(file);

}
int Add(char* lname, char* fname, char* email) {
	int i;
	for (i = 0; i < CRecord; i++) {
		if (new_record[i].next == NULL) {
			break;
		}
	}
	struct RECORD* checkpoint = new_record;
	new_record = (struct RECORD*)realloc(new_record, sizeof(struct RECORD) * (CRecord + 2));
	uintptr_t diff = (uintptr_t)new_record - (uintptr_t)checkpoint;

	for (int j = 0; j < CRecord; j++) {
		if (new_record->next != NULL) {
			new_record[j].next = (struct RECORD*)((uintptr_t)new_record[j].next + diff);
		}
	}
	head = (struct RECORD*)((uintptr_t)head + diff);
	strcpy(new_record[CRecord].lname, lname);
	strcpy(new_record[CRecord].fname, fname);
	strcpy(new_record[CRecord].email, email);
	new_record[CRecord].id = id;
	id++;
	new_record[CRecord].next = NULL;
	new_record[i].next = &new_record[CRecord];
	CRecord++;

	return 0;
}
int Delete(int CID) {
	int i;
	int si = 0; //i�̕ۑ��ϐ�
	int check_F = 2; //�N���C�A���g�`�F�b�N�t���O

	for (i = 0; i < CRecord; i++) {
		if (new_record[i].id == CID) {
			printf("%d", new_record[i].id);
			check_F = 3;
			si = i;
		}
	}
	if (check_F == 2) {
		printf("�f�[�^��������܂���ł����B\n");
	}
	while (check_F != 2) {
		printf("Lastname:%s Firstname: %s email :%s ���폜���܂���?\n �͂�>>>1 ������>>>2 \n", new_record[si].lname, new_record[si].fname, new_record[si].email);
		scanf("%d", &check_F);
		//�����͂�������
		if (check_F == 1) {
			if (&new_record[si] == head) {
				head = head->next;
			}
			for (i = 0; i < CRecord; i++) {
				if (new_record[i].next == &new_record[si]) {
					new_record[i].next = new_record[si].next;
				}
			}
			new_record[si] = new_record[CRecord - 1];
			for (i = 0; i < CRecord; i++) {
				if (new_record[i].next == &new_record[CRecord - 1]) {
					new_record[i].next = &new_record[si];
				}
			}
			new_record = (struct RECORD*)realloc(new_record, sizeof(struct RECORD) * (CRecord - 1));
			CRecord--;
			check_F++;
		}
	}
	return 0;
}
int Find(int find_F) {
	char lname[64];
	int check_F = 0;
	if (find_F == 1) {
		printf("�����������c������͂��Ă�������\n>>>");
		scanf("%s", lname);
		for (int i = 0; i < CRecord; i++) {
			if (strcmp(new_record[i].lname, lname) == 0) {
				printf("id: %d Lastname:%s Firstname: %s email :%s\n", new_record[i].id, new_record[i].lname, new_record[i].fname, new_record[i].email);
				check_F++;

			}
		}
		if (check_F == 0) {
			printf("�f�[�^��������܂���ł���\n");
		}
	}
	else if (find_F == 2) {
		printf("�������������O����͂��Ă�������\n>>>");
		scanf("%s", lname);
		for (int i = 0; i < CRecord; i++) {
			if (strcmp(new_record[i].fname, lname) == 0) {
				printf("id: %d Lastname:%s Firstname: %s email :%s\n", new_record[i].id, new_record[i].lname, new_record[i].fname, new_record[i].email);
				check_F++;
			}
		}
		if (check_F == 0) {
			printf("�f�[�^��������܂���ł���\n");
		}
	}
	else {
		printf("�������������[���A�h���X����͂��Ă�������\n>>>");
		scanf("%s", lname);
		for (int i = 0; i < CRecord; i++) {
			if (strcmp(new_record[i].email, lname) == 0) {
				printf("id: %d Lastname:%s Firstname: %s email :%s\n", new_record[i].id, new_record[i].lname, new_record[i].fname, new_record[i].email);
				check_F++;
			}
		}
		if (check_F == 0) {
			printf("�f�[�^��������܂���ł���\n");
		}
	}
	return 0;
}
int Sort(int key, int UpDown) {
	//�}���\�[�g���g�p
	struct RECORD* first_data = NULL, * finish_data, * sort_data, * save_data, * p_data;

	first_data = head;
	finish_data = first_data->next;
	if (UpDown == 1) {
		for (int i = 1; i < CRecord; i++) {
			save_data = first_data;
			for (int k = 0; k < CRecord; k++) {
				if (first_data->next == finish_data) {
					first_data->next = finish_data->next;
					break;
				}
				first_data = first_data->next;
			}
			first_data = save_data;
			save_data = finish_data->next;
			sort_data = first_data;
			p_data = NULL;
			for (int j = 0; j < i; j++) {
				if (key == 1) {//last name
					if (strcmp(finish_data->lname, sort_data->lname) > 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}

				}
				if (key == 2) {//first name
					if (strcmp(finish_data->fname, sort_data->fname) > 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}

				}
				if (key == 3) {//email
					if (strcmp(finish_data->email, sort_data->email) > 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}
				}
			}
			if (p_data != NULL) {
				p_data->next = finish_data;
			}
			else {
				first_data = finish_data;
			}
			finish_data->next = sort_data;
			finish_data = save_data;
		}
	}
	if (UpDown == 2) {
		for (int i = 1; i < CRecord; i++) {
			save_data = first_data;
			for (int k = 0; k < CRecord; k++) {
				if (first_data->next == finish_data) {
					first_data->next = finish_data->next;
					break;
				}
				first_data = first_data->next;
			}
			first_data = save_data;
			save_data = finish_data->next;
			sort_data = first_data;
			p_data = NULL;
			for (int j = 0; j < i; j++) {
				if (key == 1) {//last name
					if (strcmp(finish_data->lname, sort_data->lname) < 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}

				}
				if (key == 2) {//first name
					if (strcmp(finish_data->fname, sort_data->fname) < 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}

				}
				if (key == 3) {//email
					if (strcmp(finish_data->email, sort_data->email) < 0) {
						p_data = sort_data;
						sort_data = sort_data->next;
					}
				}
			}
			if (p_data != NULL) {
				p_data->next = finish_data;
			}
			else {
				first_data = finish_data;
			}
			finish_data->next = sort_data;
			finish_data = save_data;
		}
	}
	head = first_data;
	for (int i = 0; i < CRecord; i++) {
		printf("id: %d Lastname:%s Firstname: %s email :%s\n", first_data->id, first_data->lname, first_data->fname, first_data->email);
		first_data = first_data->next;
	}
	return 0;
}
int WriteData() {
	FILE* file = fopen("datef.txt", "w");
	if (file == NULL) {
		printf("�t�@�C�����J���܂���ł����B\n");
		exit(1);
	}
	fprintf(file, "%d\n", CRecord);
	for (int i = 0; i < CRecord; i++) {

		fprintf(file, "%s %s %s\n", new_record[i].lname, new_record[i].fname, new_record[i].email);
	}

	fclose(file);
	return 0;
}

int main(void) {

	FILE* file = fopen("datef.txt", "r");
	read_data(file);
	int choice_F = 0;

	while (choice_F != 6) {
		printf("Please select a mode\n");
		printf(" 1:���̒ǉ� \n 2:���̍폜 \n 3:���̌��� \n 4:���̕��ёւ�\n 5:�I��\n");
		printf(">>>>");
		scanf("%d", &choice_F);
		switch (choice_F)
		{
		case 1: {
			char lname[64];
			char fname[64];
			char email[64];
			printf("last name>>>");
			scanf("%s", lname);
			printf("first name>>>");
			scanf("%s", fname);
			printf("email>>>");
			scanf("%s", email);
			Add(lname, fname, email);
			break;
		}
		case 2: {
			int CID;
			for (int i = 0; i < CRecord; i++) {
				printf("id: %d Lastname:%s Firstname: %s email :%s\n", new_record[i].id, new_record[i].lname, new_record[i].fname, new_record[i].email);
			}
			printf("�폜�������ID����͂��Ă�������: ");
			scanf("%d", &CID);
			Delete(CID);
			break;
		}
		case 3: {
			int find_F;
			int check_F = 0;
			while (check_F == 0) {
				printf("�����������f�[�^�̎�ނ���͂��Ă�������\n  Last name>>>1 First name>>>2 email>>>3\n>>>");
				scanf("%d", &find_F);
				if (find_F >= 1 && find_F <= 3) {
					Find(find_F);
					check_F++;
				}
				else {
					printf("���͂���蒼���Ă�������\n");
				}
			}
			break;
		}
		case 4: {
			int key, UpDown;

			printf("�ǂ̃L�[���g�p���܂���\n�@Last name>>>1 First name>>>2 email>>>3\n>>>");
			scanf("%d", &key);
			printf("����or�~���H\n ����>>>1 �~��>>>2\n");
			scanf("%d", &UpDown);
			Sort(key, UpDown);
			break;
		}
		case 5:
			WriteData();
			choice_F++;
			printf("�ݒ��ۑ����܂���");
			break;
		default:
			printf("Not defined\n");
			break;
		}
	}

}