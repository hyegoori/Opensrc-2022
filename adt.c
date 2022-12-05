#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996) // Visual Studio 사용 시 추가! (strcpy() 때문에 필요)
#define MAX_IOT_LIST_SIZE 45

typedef struct
{
    char name[20]; // 이름
    int id;        // 학번
} Namecard;

Namecard iot_list[MAX_IOT_LIST_SIZE]; // 학생 정보를 저장할 배열
int length;                           // 리스트의 길이
Namecard make_Namecard(char name[], int id)
{ // Namecard 생성 함수
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
 ? 리스트가 비어 있으면 1, 그렇지 않으면 0을 리턴
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
 ? 리스트가 가득 차 있으면 1, 그렇지 않으면 0을 리턴
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
        printf("포화상태 오류 또는 삽입 위치 오류 \n");
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
        printf("공백상태 오류 또는 삭제 위치 오류 \n");
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
        printf("교체 위치 오류 \n");
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

    insert(0, make_Namecard("김대희", 20170031)); // 본인 이름, 학번 넣기
    insert(0, make_Namecard("서재연", 2011521));
    insert(1, make_Namecard("김준형", 20211516));
    insert(size(), make_Namecard("서승진", 20211506));
    insert(3, make_Namecard("신서연", 20211501));
    insert(size(), make_Namecard("김지연", 20211530));
    insert(10, make_Namecard("김현수", 20211522));
    print_list("Insert");
    replace(size() - 1, make_Namecard("정현", 20211504));
    replace(4, make_Namecard("채경훈", 20211498));
    replace(20, make_Namecard("허정인", 20211490));
    print_list("Replace");
    delete (3);
    delete (size() - 1);
    delete (0);
    delete (30);
    print_list("Delete");
    sort_list();
    print_list("Sort");
    printf("%s is found at %d\n", "김준형", find(make_Namecard("김준형", 20211516)));
    printf("%s is found at %d\n", "김정우", find(make_Namecard("김정우", 20211526)));
    printf("%s is found at %d\n", "채경훈", find(make_Namecard("채경훈", 20211234)));
}
