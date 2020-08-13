/*
** EPITECH PROJECT, 2019
** my_sort_int_array
** File description:
** hello
*/

int *my_sort_int_array(int *array, int size)
{
    int mv = 1;
    int temp;

    size--;
    while (mv != 0){
        mv = 0;
        for (int i = 0; i < size; i++){
            if (array[i] > array[i + 1]){
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                mv++;
            }
        }
    }
    return (array);
}
