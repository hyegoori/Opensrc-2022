#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996) // Visual Studio ��� �� �߰�! (strcpy() ������ �ʿ�)
#define MAX_IOT_LIST_SIZE 45

typedef struct
{
    char name[20]; // �̸�
    int id;        // �й�
} Namecard;

Namecard iot_list[MAX_IOT_LIST_SIZE]; // �л� ������ ������ �迭
int length;                           // ����Ʈ�� ����
Namecard make_Namecard(char name[], int id)
{ // Namecard ���� �Լ�
    Namecard newCard;
    strcpy(newCard.name, name);
    newCard.id = id;
    return newCard;
}

void init()
{
    length = 0;
}

/**
 ? ����Ʈ�� ��� ������ 1, �׷��� ������ 0�� ����
 */
int is_empty()
{
    if (length == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/**
 ? ����Ʈ�� ���� �� ������ 1, �׷��� ������ 0�� ����
 */
int is_full(void)
{
    if (length == MAX_IOT_LIST_SIZE)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void insert(int pos, Namecard namecard)
{

    int i;
    if (is_full() == 0 && pos >= 0 && pos <= length)
    {
        for (i = length; i > pos; i--)
        {
            iot_list[i] = iot_list[i - 1];
        }

        iot_list[pos] = namecard;
        length++;
    }
    else
    {
        printf("��ȭ���� ���� �Ǵ� ���� ��ġ ���� \n");
    }
}
void delete (int pos)
{
    int i;
    if (is_empty() == 0 && pos >= 0 && pos < length)
    {
        for (i = pos; i < length; i++)
        {
            iot_list[i] = iot_list[i + 1];
        }
        length--;
    }
    else
    {
        printf("������� ���� �Ǵ� ���� ��ġ ���� \n");
    }
}

void replace(int pos, Namecard item)
{

    int i;
    if (is_full() == 0 && pos >= 0 && pos <= length)
    {
        iot_list[pos] = item;
    }
    else
    {
        printf("��ü ��ġ ���� \n");
    }
}

Namecard get_entry(int pos)
{
    Namecard iItem = iot_list[pos];
    return iItem;
}

int find(Namecard item)
{
    int i;
    if (is_empty() == 0)
    {
        for (i = 0; i < length; i++)
        {
            Namecard iItem = get_entry(i);
            printf("(%s, %d) ", iItem.name, iItem.id);
            if (iItem.id == item.id && strcmp(iItem.name, item.name) == 0)
            {
                return i;
            }
        }
    }

    return -1;
}

int size()
{
    return length;
}

void sort_list(void)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            Namecard iItem = get_entry(i);
            Namecard jItem = get_entry(j);

            if (iItem.id > jItem.id)
            {
                replace(j, iItem);
                replace(i, jItem);
            }
        }
    }
}

void print_list(char *msg)
{
    int i;
    printf("%s: ", msg);

    for (i = 0; i < length; i++)
    {
        Namecard temp = get_entry(i);
        printf("(%s, %d) ", temp.name, temp.id);
    }

    printf("\n\n");
}

int main()
{
    init();
    print_list("Init");

    insert(0, make_Namecard("�����", 20170031)); // ���� �̸�, �й� �ֱ�
    insert(0, make_Namecard("���翬", 2011521));
    insert(1, make_Namecard("������", 20211516));
    insert(size(), make_Namecard("������", 20211506));
    insert(3, make_Namecard("�ż���", 20211501));
    insert(size(), make_Namecard("������", 20211530));
    insert(10, make_Namecard("������", 20211522));
    print_list("Insert");
    replace(size() - 1, make_Namecard("����", 20211504));
    replace(4, make_Namecard("ä����", 20211498));
    replace(20, make_Namecard("������", 20211490));
    print_list("Replace");
    delete (3);
    delete (size() - 1);
    delete (0);
    delete (30);
    print_list("Delete");
    sort_list();
    print_list("Sort");
    printf("%s is found at %d\n", "������", find(make_Namecard("������", 20211516)));
    printf("%s is found at %d\n", "������", find(make_Namecard("������", 20211526)));
    printf("%s is found at %d\n", "ä����", find(make_Namecard("ä����", 20211234)));
}
