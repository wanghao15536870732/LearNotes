#define _CRT_SECURE_NO_WARNINGS

#include "stdlib.h"
#include "string.h"
#include "ArrayText.c"

void init(seqstack *st)
{
    st->top = 0;
}
void push(seqstack *st, int x)
{
    if (st->top == MAXSIZE)
    {
        printf("\nջ������!");
        exit(1);
    }
    st->a[st->top] = x;
    st->top++;
}

int pop(seqstack *st)
{
    if (st->top == 0)
    {
        printf("\nջ�ǿյ�!");
        exit(1);
    }
    st->top--;
    return st->a[st->top];
}
//���ı�������ȡ���ݣ������ڽӱ�洢
void ReadFromFile(TextCompiler *text, char *filename)
{
    text->count = 0; //ÿ���кŸ�0
    Word *word;      //�µĽ��
    FILE *file;
    Word *p = NULL;
    file = fopen(filename, "r"); //���ļ�
    int i = 0;                   //���±�
    int j = -1;                  //���±�
    if (file)
    {
        word = (Word *)malloc(sizeof(Word)); //����һ���µĿռ�
        word->length = 0;                    //��ʼ��ֵÿһ�г���Ϊ0
        while ((word->data[i] = fgetc(file)) != EOF)
        {
            if (word->data[i] == '\n') //�����ȡ������ַ���'\n'
            {
                word->data[i] = '\0';                //��仰��ȡ����������'\0'
                j++;                                 //������һ�ٸ�ֵ
                text->column[j].FirstWord = word;    //����ȡ����һ�����ӵ�����ĺ���
                word = (Word *)malloc(sizeof(Word)); //�ٴο���һ���µ�word
                word->length = 0;                    //��ʼ��ֵ����Ϊ0
                i = 0;                               //�ٴδ�i=0��ʼѭ��
                text->count++;                       //����������1
            }
            else
            {
                i++;            //��һ�л�û�ж�ȡ�������±���������ȡ
                word->length++; //ÿһ�е��ַ�������һ
            }
        }
        printf("�ļ����ݶ�ȡ�ɹ�!!!\n");
    }
    else
        printf("�ļ���ʧ�ܣ�\n");
    fclose(file); //�ر��ļ�
}

//�������
void EasyOutput(TextCompiler *text)
{
    if (text == NULL)
    {
        printf("�����ı�Ϊ�գ������ԣ�\n");
        exit(0);
    }
    for (int i = 0; i < text->count; i++)
        printf("%s\n", text->column[i].FirstWord->data);
}

//ͳ�������ı��������ַ��ĸ���
int TheLetterNumberOfText(TextCompiler *text)
{
    int count = 0; //������
    int j;         //�����±��¼
    for (int i = 0; i < text->count; i++)
    {
        j = 0;
        while (text->column[i].FirstWord->data[j] != '\0')
        {
            j++;     //�����±��ƶ�
            count++; //�������
        }
    }
    return count;
}
//ͳ�������ı������е��ʵĸ���
int TheWordNumberOfText(TextCompiler *text)
{
    int count = 0; //������
    int m;         //�����±��¼
    int n;
    for (int i = 0; i < text->count; i++)
    {
        m = 0;
        n = 1;
        while (text->column[i].FirstWord->data[n] != '\0')
        {
            if (text->column[i].FirstWord->data[m] != ' ' &&
                (text->column[i].FirstWord->data[n] == ' ' ||
                 text->column[i].FirstWord->data[n] == '.' ||
                 text->column[i].FirstWord->data[n] == '!' ||
                 text->column[i].FirstWord->data[n] == '?' ||
                 text->column[i].FirstWord->data[n] == '\"'))
                count++;
            n++; //�����±��ƶ�
            m++;
        }
    }
    return count;
}
//kmp�㷨ƥ���ַ���
void StringNumber(TextCompiler *text)
{
    int length = text->column[0].FirstWord->length; //�����һ�е�����
    char vis2[MAXSIZE] = {0}, vis1[1000] = {0};
    int next[1000] = {0};
    int count = 0;
    seqstring str;
    str.length = 0;
    TableToArray(text, &str);
    strcpy(vis1, str.str);
    count = 0;
    printf("��������Ҫ��ѯ���Ӵ���\n");
    getchar();
    gets_s(vis2);
    get_next(next, vis2, next);
    count = kmp(vis1, vis2, next, length);
    printf("\n�ַ��� %s �������г��ִ���Ϊ��%d\n\n", vis2, count);
}

//����ÿһ�е������ַ�
void RowNumber(TextCompiler *text)
{
    int row = 0;
    int input = 0;
    printf("\t1.ͳ����ƪ���µĿո�ĸ���\n");
    printf("\t2.ͳ����ƪ���µ���ĸ�ĸ���\n");
    printf("\t3.ͳ��ĳһ�ַ����������г��ֵĴ���\n");
    printf("\t4.ͳ����ƪ���µ��ַ�����\n");
    printf("\t5.ͳ����ƪ���µĵ��ʸ���\n");
    printf("�����빦�ܱ�ţ�\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
    {
        int count = 0; //������
        int i = 0;     //����±�
        for (int row = 0; row < text->count; row++)
        {
            i = 0;
            while (text->column[row].FirstWord->data[i] != '\0')
            {
                if (text->column[row].FirstWord->data[i] == ' ') //�ж��Ƿ�Ϊ�ո�
                    count++;                                     //������
                i++;                                             //�±��1
            }
        }
        printf("��ƪ�ı�����%d���ո�\n", count);
        break;
    }
    case 2:
    {
        int count = 0; //������
        int i = 0;     //����±�
        char letter;
        for (int row = 0; row < text->count; row++)
        {
            i = 0;
            while ((letter = text->column[row].FirstWord->data[i]) != '\0')
            {
                if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) //�жϸ��ַ��Ƿ��������Χ֮��
                    count++;                                                              //������
                i++;                                                                      //�±�����ߣ���������
            }
        }
        printf("��ƪ�ı�����%d����ĸ\n", count);
        break;
    }
    case 3:
    {
        StringNumber(text);
        break;
    }
    case 4:
    {
        printf("��ƪ�ı�����%d���ַ�\n", TheLetterNumberOfText(text));
        break;
    }
    case 5:
    {
        printf("��ƪ�ı�����%d������\n", TheWordNumberOfText(text));
        break;
    }
    default:
        printf("�������󣡣���\n");
        exit(0);
        break;
    }
}

//kmpģʽƥ��
void kmpmatch(TextCompiler *text)
{
    int i = 0, plength = 0;
    char p[20] = {0};
    printf("��������Ҫ���ҵĵ���:\n");
    scanf("%s", p);
    while (p[i])
    {
        plength++; //��ȡ�����ַ����ĳ���
        i++;       //�ַ����±������ƶ�
    }
    p[plength] = '\0'; //���һλ����Ϊ'\0'
}

void chinesematch(TextCompiler *text, seqstack *st) //���Ĳ���
{
    int i = 0, j, k, m = 0, succ, q, plength = 0;
    char p[20] = {0};
    printf("��������Ҫ���ҵĺ���:\n");
    scanf("%s", p);
    while (p[i]) //ͳ��
    {
        plength++;
        i++;
    }
    p[plength] = '\0';
    for (k = 0; k < text->count; k++)
    {
        i = 0;
        q = text->column[k].FirstWord->length;
        while (i <= q - plength)
        {
            j = 0;
            succ = 1;
            while ((j <= plength - 1) && succ)
            {
                if (p[j] == text->column[k].FirstWord->data[i + j])
                    j++;
                else
                    succ = 0;
            }
            i++;
            if (succ)
            {
                printf("ƥ��ɹ���λ���ڵ�%d�е�%d��\n", k + 1, i - 1);
                push(st, i - 1);
                push(st, k + 1);
                succ = 0;
            }
        }
    }
    if (st->top == 0)
        printf("ƥ��ʧ�ܣ���\n");
}
void englishmatch(TextCompiler *text, seqstack *st) //Ӣ�Ĳ���
{
    int i = 0, j, k, m = 0, succ, q, plength = 0;
    char p[20] = {0};
    printf("��������Ҫ���ҵĵ���:\n");
    //scanf("%s", p);
    getchar();
    gets_s(p);
    while (p[i])
    {
        plength++;
        i++;
    }
    p[plength] = '\0';
    for (k = 0; k < text->count; k++)
    {
        i = 0;
        q = text->column[k].FirstWord->length;
        while (i <= q - plength)
        {
            j = 0;
            succ = 1;
            while ((j <= plength - 1) && succ)
            {
                if (p[j] == text->column[k].FirstWord->data[i + j])
                    j++;
                else
                    succ = 0;
            }
            if (text->column[k].FirstWord->data[i + j] == ' ' &&
                text->column[k].FirstWord->data[i - 1] == ' ') //�ж��ַ��������Ƿ�Ϊ' '
                i++;
            else if (text->column[k].FirstWord->data[i + j] == ' ' &&
                     k == 0) //�ж���ƪ���µĵ�һ������
                i++;
            else if (text->column[k].FirstWord->data[i + j] == ' ' &&
                     text->column[k - 1].FirstWord->data[m] == '\0') //�ж�ÿ�еĵ�һ�������Ƿ�Ϊ
                i++;
            else
            {
                succ = 0;
                i++;
            }
            if (succ)
            {
                printf("ƥ��ɹ���λ���ڵ�%d�е�%d��\n", k + 1, i - 1);
                push(st, i - 1); //д��ջ��������һ�ε���
                push(st, k + 1);
                succ = 0;
            }
        }
    }
    if (st->top == 0)
        printf("ƥ��ʧ�ܣ���\n");
}

//����ģʽƥ��
void nativematch(TextCompiler *text, seqstack *st)
{
    int input = 0;
    printf("��ѡ����Ҫ���ҵ���������:1.���� 2.Ӣ��\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
        chinesematch(text, st);
        break;
    case 2:
        englishmatch(text, st);
        break;
    default:
    {
        printf("�������󣡣�\n");
        exit(0);
        break;
    }
    }
}

//������д���ļ�
void PutInFile(char *filename, seqstring *array, int roww)
{
    int row; //ÿһ��������������
    row = roww;
    FILE *fp;
    int save = 0; //����д���ļ��ķ���ֵ
    int count = 0;
    fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
    if (fp)
    {
        while (array->str[count] != '\0')
        {
            save = fputc(array->str[count], fp);
            if (save == -1) //�������-1,�����ļ�д��ʧ��
            {
                printf("д���ļ�ʧ�ܣ�����\n");
                exit(0); //�˳�
            }
            count++; //д���ַ���1
            if (count % row == 0)
                fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
        }
        fputc('\n', fp);
    }
    else
        printf("�ļ���ʧ�ܣ���\n");
    fclose(fp);
}

void IntoFile(TextCompiler *text, char *filename, int length)
{
    seqstring strtr;
    strtr.length = 0;
    TableToArray(text, &strtr);
    PutInFile(filename, &strtr, length);
}

//ɾ��ָ���Ӵ�
void StrDelete(TextCompiler *text, char *filename)
{
    if (text->count == 0)
        printf("�ı�����Ϊ�գ���\n");
    else
    {
        int length = text->column[0].FirstWord->length; //�ȱ����һ�еĳ���
        seqstring str;
        str.length = 0;
        int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
        char p[20] = {0};
        printf("��������Ҫɾ�������ַ���:\n");
        getchar();
        gets_s(p);
        while (p[i])
        {
            plength++; //��ȡ�����ַ����ĳ���
            i++;       //�ַ����±������ƶ�
        }
        p[plength] = '\0';                //���һλ����Ϊ'\0'
        for (k = 0; k < text->count; k++) //ѭ������ÿһ��
        {
            i = 0;
            q = text->column[k].FirstWord->length; //����һ�³���
            while (i <= q - plength)
            {
                j = 0;
                succ = 1;
                while ((j <= plength - 1) && succ) //û��ƥ������ұ�־λ��1
                {
                    if (p[j] == text->column[k].FirstWord->data[i + j])
                        j++;
                    else
                        succ = 0;
                }
                i++;
                if (succ)
                {
                    strdelete(text->column[k].FirstWord, i, plength); //ɾ�����ַ���
                    succ = 0;                                         //��־λ�����趨Ϊ0
                }
            }
        }
        IntoFile(text, filename, length); //ת��������д���ļ�
        ReadFromFile(text, filename);
        printf("ɾ������ַ���:\n");
        EasyOutput(text);
    }
}

void strdelete2(TextCompiler *text, seqstack *st, char *filename)
{
    int length = text->column[0].FirstWord->length;
    char route[MAXSIZE] = {0};
    int k, h = 0, l = 0, r = 0, z, d, i, q = 0, c = 0;
    printf("������Ҫ���Ҳ�ɾ���ĵ��ʣ�\n");
    nativematch(text, st);
    printf("������Ҫɾ���ĵ������ڵ�λ�ã�\n");
    printf("�кţ�");
    scanf("%d", &h);
    printf("�кţ�");
    scanf("%d", &l);
    int count = 0; //�����±�
    for (i = 0; i < h - 1; i++)
    {
        int k = 0; //�ڽӱ��ÿһ��������±�
        while (text->column[i].FirstWord->data[k] != '\0')
        {
            char letter = text->column[i].FirstWord->data[k];
            route[count] = letter;
            count++; //����������±��1
            k++;     //�ڽӱ�������±��1
        }
        r = r + k;
        //printf("��%d����%d��Ԫ��:",i+1,r);
    }
    z = r + l; //zΪɾ������ʼλ��
    count = 0;
    for (i = 0; i < text->count; i++)
    {
        int mn = 0; //�ڽӱ��ÿһ��������±�
        while (text->column[i].FirstWord->data[mn] != '\0')
        {
            char letter = text->column[i].FirstWord->data[mn];
            route[count] = letter;
            count++; //����������±��1
            mn++;    //�ڽӱ�������±��1
        }
    }
    route[count] = '\0'; //�������һλ��ֵ'\0'
    if (z < 1)
        printf("cannot delete\n");
    else
    {
        for (d = r + q + l; d < c; d++)
            route[d - q] = route[d]; //qΪɾ���ĵ��ʵĳ���
        count = count - q;
        route[count] = '\0';
    }
    printf("ɾ������ַ���Ϊ��\n");
    for (int j = 0; j < count / length; j++)
    {
        for (int i = j * length; i < j * length + length; i++)
            printf("%c", route[i]);
        printf("\n");
    }
}

//���ַ����滻
void StrReplace(TextCompiler *text, char *filename)
{
    int length = text->column[0].FirstWord->length;
    Word word;
    word.length = 0;
    seqstring str;
    str.length = 0;
    int i = 0, j, k, m = 0, succ = 0, q, plength = 0;
    char p[20] = {0};
    printf("��������Ҫ���滻���ַ���:\n");
    getchar();
    gets_s(p);
    printf("��������Ҫ�滻���ַ�����\n");
    //getchar();
    gets_s(word.data);
    //scanf("%s", word.data);
    while (p[i])
    {
        plength++; //��ȡ�����ַ����ĳ���
        i++;       //�ַ����±������ƶ�
    }
    p[plength] = '\0'; //���һλ����Ϊ'\0'
    while (word.data[word.length])
        word.length++;
    for (k = 0; k < text->count; k++) //ѭ������ÿһ��
    {
        i = 0;
        q = text->column[k].FirstWord->length; //����һ�³���
        while (i <= q - plength)
        {
            j = 0;
            succ = 1;
            while ((j <= plength - 1) && succ) //û��ƥ������ұ�־λ��1
            {
                if (p[j] == text->column[k].FirstWord->data[i + j])
                    j++;
                else
                    succ = 0;
            }
            i++;
            if (succ)
            {
                strreplace(text->column[k].FirstWord, i - 1, &word, plength); //�滻���ַ���
                succ = 0;                                                     //��־λ�����趨Ϊ0
            }
        }
    }
    printf("�滻����ı���\n");
    IntoFile(text, filename, length);
    ReadFromFile(text, filename);
    EasyOutput(text);
}

//���ҡ��滻��ɾ��
void SearchReplaceDelete(TextCompiler *text, seqstack *st, char *filename)
{
    if (text == NULL)
    {
        printf("�����ı�Ϊ�գ������ļ�·���Ƿ�����\n");
        exit(0);
    }
    int input = 0;
    printf("\t1.�ַ�������\n");
    printf("\t2.�ַ����滻\n");
    printf("\t3.�ַ�������\n");
    printf("\t4.�ַ���ɾ��\n");
    printf("�����빦�ܱ�ţ�\n");
    scanf("%d", &input);
    switch (input)
    {
    case 1:
    {
        StringNumber(text);
        break;
    }
    case 2:
    {
        StrReplace(text, filename);
        break;
    }
    case 3:
    {
        int input = 0;
        printf("������Ҫ�в��뻹���в��룿\n");
        printf("\t1.�ַ������в���\n");
        printf("\t2.�ַ������в���\n");
        printf("\t3.�ַ����Ŀ����\n");
        printf("�����������ţ�\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
        {
            Word word;
            word.length = 0;
            int row = 0, column = 0; //�����и���
            int length = text->column[0].FirstWord->length;
            printf("�������Ҫ�����λ�ã�(�и���)\n");
            printf("�кţ�");
            scanf("%d", &row);
            printf("�кţ�");
            scanf("%d", &column);
            printf("��������Ҫ������ַ�����\n");
            getchar();
            gets_s(word.data);
            while (word.data[word.length])
                word.length++;
            strinsert(text->column[row - 1].FirstWord, column, &word);
            IntoFile(text, filename, length);
            ReadFromFile(text, filename);
            printf("\n\n�ڵ�%d��%d�� ���� ���%s���ַ�������ı�Ϊ��\n\n", row, column, word.data);
            EasyOutput(text);
            break;
        }
        case 2:
        { //�еĲ���
            int dlength = 0;
            int col = 0;
            char data[100] = {0};
            int length = text->column[0].FirstWord->length;
            int row = 0, column = 0; //�����и���
            printf("�������Ҫ�����λ�ã�(�и���)\n");
            printf("�кţ�");
            scanf("%d", &row);
            printf("�кţ�");
            scanf("%d", &column);
            printf("��������Ҫ������ַ�����\n");
            scanf("%s", data);
            while (data[dlength]) //ͳ�������ַ����ĳ���
                dlength++;
            for (int i = row - 1; i < row + dlength; i++) //ѭ�����������������������ַ����ĳ���
            {
                Word *word = text->column[i].FirstWord;
                for (int j = word->length - 1; j >= column; j--) //ѭ����ָ������
                    word->data[j + 1] = word->data[j];
                if (data[col] != '\0')
                    word->data[column] = data[col++];
                word->length++;
                word->data[word->length] = '\0';
            }
            printf("\n\n�ڵ�%d��%d�� ���� ���%s���ַ�������ı�Ϊ��\n\n", row, column, data);
            EasyOutput(text);
            IntoFile(text, filename, length);
            break;
        }
        case 3:
        { //��Ĳ���
            int row = 0, column = 0;
            int width = 0, length = 0;
            Word word;
            word.length = 0;
            printf("��������Ҫ�������кš��кš���Ŀ�ȡ���ĳ��ȣ�\n");
            printf("�кţ�");
            scanf("%d", &row);
            printf("�кţ�");
            scanf("%d", &column);
            printf("���ȣ�");
            scanf("%d", &width);
            printf("��ȣ�");
            scanf("%d", &length);
            if (row + length > text->count || column + width > text->column[0].FirstWord->length)
            {
                printf("������λ�����������ԣ���\n");
                exit(0);
            }
            else
            {
                char filename11[20] = "D:\\Desktop\\Test.txt";
                seqstring str;
                str.length = 0;
                printf("�������Ҫ������ı���\n");
                getchar();
                gets_s(str.str);
                while (str.str[str.length])
                    str.length++;
                PutInFile(filename11, &str, width);
                TextCompiler text1;
                ReadFromFile(&text1, filename11);
                int j;
                for (int i = row, j = 0; i < row + length, j < length; i++, j++)
                    strinsert(text->column[i].FirstWord, column, text1.column[j].FirstWord);
            }
            EasyOutput(text);
            break;
        }
        default:
            break;
        }
        break;
    }
    case 4:
    {
        int input = 0;
        printf("������Ҫ��ɾ��������ɾ����\n");
        printf("\t1.��ɾ��\n");
        printf("\t2.��ɾ��\n");
        printf("\t3.���ɾ��\n");
        printf("�����������ţ�\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
        { //�ַ�����ɾ��
            StrDelete(text, filename);
            break;
        }
        case 2:
        { //�ַ�����ɾ��
            int column = 0;
            printf("��������Ҫɾ�����кţ�\n");
            scanf("%d", &column);
            for (int i = 0; i < text->count; i++)
                strdelete(text->column[i].FirstWord, column, 1);
            break;
        }
        case 3:
        {
            int row = 0, column = 0;
            int width = 0, length = 0;
            int lengthh = text->column[0].FirstWord->length; //�����ı���һ�еĳ���
            printf("��������Ҫɾ������кš��кš���ȡ����ȣ�\n");
            printf("�кţ�");
            scanf("%d", &row);
            printf("�кţ�");
            scanf("%d", &column);
            printf("���ȣ�");
            scanf("%d", &width);
            printf("��ȣ�");
            scanf("%d", &length);
            if (row + length > text->count || column + width > text->column[0].FirstWord->length)
            {
                printf("����������,�������������\n");
                exit(0);
            }
            for (int i = row - 1; i < row + length; i++)
                strdelete(text->column[i].FirstWord, column, length);
            IntoFile(text, filename, length);
            break;
        }
        default:
        {
            printf("�������󣡣�\n");
            exit(0);
            break;
        }
        }
        EasyOutput(text); //�����
        break;
    }
    default:
        printf("��������\n");
        exit(0);
        break;
    }
}

void strRemove(TextCompiler *text, char *filename)
{
    if (text->count == 0)
        printf("�ĵ�Ϊ�գ������ԣ�\n");
    else
    {
        int input = 0;
        printf("\t1.�ַ��������ƶ�\n");
        printf("\t2.�ַ��������ƶ�\n");
        printf("\t3.�ַ����Ŀ��ƶ�\n");
        printf("�����������ţ�\n");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
        {                 //�ַ��������ƶ�
            int row1 = 0; //�ƶ�ǰ����λ��
            int row2 = 0; //�ƶ�ǰ��
            printf("��������Ҫ�ƶ��е�λ�ã�\n");
            scanf("%d", &row1);
            printf("��������Ҫ�ƶ�����λ�ã�\n");
            scanf("%d", &row2);
            Word *word = text->column[row1 - 1].FirstWord; //���������Ҫ��������һ��
            for (int i = row1; i < row2; i++)
                text->column[i - 1].FirstWord = text->column[i].FirstWord;
            text->column[row2 - 1].FirstWord = word;
            printf("���ƶ�����ı�:\n");
            EasyOutput(text);            //�����
            TableToFile(text, filename); //д���ļ�
            break;
        }
        case 2:
        {                    //�ַ��������ƶ�
            int column1 = 0; //�ƶ�ǰ����λ��
            int column2 = 0; //�ƶ�ǰ��
            printf("��������Ҫ�ƶ��е�λ�ã�\n");
            scanf("%d", &column1);
            printf("��������Ҫ�ƶ��е�λ�ã�\n");
            scanf("%d", &column2);
            for (int i = 0; i < text->count; i++)
            {
                char temp; //�м佻����
                temp = text->column[i].FirstWord->data[column1 - 1];
                text->column[i].FirstWord->data[column1 - 1] = text->column[i].FirstWord->data[column2 - 1];
                text->column[i].FirstWord->data[column2 - 1] = temp;
            }
            printf("���ƶ�����ı�:\n");
            EasyOutput(text);            //�����
            TableToFile(text, filename); //д���ļ�
            break;
        }
        case 3:
        { //�ַ����Ŀ��ƶ�
            int length_block = text->column[0].FirstWord->length;
            int row1 = 0, column1 = 0;
            int row2 = 0, column2 = 0;
            int width = 0, length = 0;
            printf("�������Ҫ�ƶ�ǰ�Ŀ���кš��кš����ȡ���ȡ���\n");
            printf("�кţ�");
            scanf("%d", &row1);
            printf("�кţ�");
            scanf("%d", &column1);
            printf("���ȣ�");
            scanf("%d", &width);
            printf("��ȣ�");
            scanf("%d", &length);
            printf("�������Ҫ�ƶ���Ŀ���кš��кţ�\n");
            printf("�кţ�");
            scanf("%d", &row2);
            printf("�кţ�");
            scanf("%d", &column2);
            int i, j;
            int m, n;
            for (i = row1 - 1, j = row2 - 1; i < row1 + length, j < row2 + length; i++, j++)
            {
                for (m = column1 - 1, n = column2 - 1; m < column1 + width, n < column2 + width; m++, n++)
                {
                    int temp = text->column[i].FirstWord->data[m];
                    text->column[i].FirstWord->data[m] = text->column[j].FirstWord->data[n];
                    text->column[j].FirstWord->data[n] = temp;
                }
            }
            for (int i = row1 - 1; i < row1 + length - 1; i++)
                strdelete(text->column[i].FirstWord, column1, length);
            printf("���ƶ�����ı���\n");
            EasyOutput(text);
            IntoFile(text, filename, length_block);
            ReadFromFile(text, filename);
            printf("�ضϺ���ı���\n");
            EasyOutput(text);
            break;
        }
        default:
            break;
        }
    }
}

void menu()
{
    puts("\n");
    printf("\t                        �����ı��༭��                    \n");
    printf("\t*\t                                                      *\n");
    printf("\t*\t 1.�����ı�����                                       *\n");
    printf("\t*\t 2.���ļ���ȡ����                                     *\n");
    printf("\t*\t 3.��������ı�                                       *\n");
    printf("\t*\t 4.ͳ��������Ӣ����ĸ���ո�������                   *\n");
    printf("\t*\t 5.ɾ��ĳһ�Ӵ�                                       *\n");
    printf("\t*\t 6.���ҡ��滻�������ַ���                             *\n");
    printf("\t*\t 7.�ַ������ƶ�                                       *\n");
    printf("\t*\t 8.����ĳ�����ʵ��кź��ڸ��г��ֵĴ����Լ�λ��       *\n");
    printf("\t*\t 9.���������                                         *\n");
    printf("\t*\t 10.�˳�                                              *\n");
}

//�û��ӽ��������ı�д�뵽�ļ�
void InputFromScreen(char *filename)
{
    int column; //ÿһ��������������
    printf("������һ����ռ��������\n");
    scanf("%d", &column);
    printf("����������Ҫ¼����ı���\n");
    char ch; //��ȡ���ַ�
    FILE *fp;
    int save = 0; //����д���ļ��ķ���ֵ
    int count = 0;
    fp = fopen(filename, "w"); //��д��ķ�ʽ���ļ�
    if (fp)
    {
        getchar();
        ch = getchar();
        while (ch != '\n')
        {
            save = fputc(ch, fp);
            count++;        //д���ַ���1
            if (save == -1) //�������-1,�����ļ�д��ʧ��
            {
                printf("д���ļ�ʧ�ܣ�����\n");
                exit(0); //�˳�
            }
            ch = getchar(); //��������ȡ����
            if (count % column == 0)
                fputc('\n', fp); //д��س��Ѵﵽ�����û��ķ�ʽ�洢�ı�
        }
        printf("����¼��ɹ�����\n");
    }
    else
        printf("�ļ���ʧ�ܣ���\n");
    fclose(fp); //�ر��ļ�
}

int main()
{
    int input = 0;
    seqstack st;
    init(&st);
    menu();
    //char filename[] = "D:\\Desktop\\Test.txt";
    char filename1[] = "D:\\Desktop\\Test2.txt";
    printf("��������ܱ�ţ�\n");
    scanf("%d", &input);
    TextCompiler text; //����һ��text
    text.count = 0;    //һ��ʼ������Ϊ0
    while (input >= 1 && input <= 10)
    {
        switch (input)
        {
        case 1:
        {
            //������Ļ¼�������д���ļ�
            InputFromScreen(filename1);
            break;
        }
        case 2:
        {
            //printf("�������ļ�·����\n");  //D:\\Desktop\\test.txt
            //scanf("%s", filename);
            ReadFromFile(&text, filename1);
            break;
        }
        case 3:
        {
            printf("�����ı�Ϊ��\n");
            EasyOutput(&text);
            break;
        }
        case 4:
        {
            RowNumber(&text);
            break;
        }
        case 5:
        {
            StrDelete(&text, filename1);
            //strdelete2(&text, &st, filename1);
            break;
        }
        case 6:
        {
            SearchReplaceDelete(&text, &st, filename1);
            break;
        }
        case 7:
        {
            strRemove(&text, filename1);
            break;
        }
        case 8:
        {
            nativematch(&text, &st);
            break;
        }
        case 9:
        {                        //��������ı�������
            if (text.count == 0) //����Ϊ0
            {
                printf("��ȡ�ı�Ϊ�գ������ԣ�\n");
                exit(0); //�˳�
            }
            else
                printf("������Ϊ:%d\n", text.count);
            break;
        }
        case 10:
        {
            exit(0);
            break;
        }
        default:
            printf("�������󣡣���\n");
            exit(0);
            break;
        }
        //menu();
        printf("��������ܱ�ţ�\n");
        scanf("%d", &input);
    }
    system("pause");
    return 0;
}