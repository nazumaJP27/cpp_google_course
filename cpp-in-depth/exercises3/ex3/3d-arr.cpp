/* TODO:
Write a program that initializes a 3-dim array and fills the 3rd dimension value with the sum of all three indexes. */

int main()
{
    int arr[3][3][3];

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            for (int l = 0; l < 3; ++l)
                arr[i][j][l] = i + j + l;
}