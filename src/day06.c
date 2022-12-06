#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void packet_detector(char input[], int distinctive_characters) 
{
    int actual = 0;
    int IP = 0;
    char packet[distinctive_characters];

    // packet is complete after 4 non repeating characters are in array, 
    // then give back how many characters had to be processed to get the packet (IP)

    // fill packet with first 4 characters
    for (int i = 0; i < distinctive_characters; i++) {
        packet[i] = input[i];
    }
    // increment IP by 4
    IP += 4;

    // check if all are non repeating
    int non_repeating = 1;
    for (int i = 0; i < distinctive_characters; i++) {
        for (int j = 0; j < distinctive_characters; j++) {
            if (i != j && packet[i] == packet[j]) {
                non_repeating = 0;
            }
        }
    }

    // if all are non repeating, return IP
    if (non_repeating) {
        actual = IP;
    }


    while (!non_repeating) {
        // check if all are non repeating
        non_repeating = 1;
        for (int i = 0; i < distinctive_characters; i++) {
            for (int j = 0; j < distinctive_characters; j++) {
                if (i != j && packet[i] == packet[j]) {
                    non_repeating = 0;
                }
            }
        }

        // if all are non repeating, return IP
        if (non_repeating) {
            actual = IP;
        }

        // if not, add next character to packet
        packet[IP % distinctive_characters] = input[IP];
        IP++;
    }

    printf("\nCharacters processed: %d", actual);
}

int main(int argc, char *argv[])
{
    char test_1[] = "bvwbjplbgvbhsrlpgdmjqwftvncz"; // 5
    char test_2[] = "nppdvjthqldpwncqszvftbrmjlhg"; // 6
    char test_3[] = "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg"; // 10
    char test_4[] = "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw"; // 11

   /*  test_case(test_1);
    test_case(test_2);
    test_case(test_3);
    test_case(test_4); */

    char* buffer = malloc(5000);
    FILE *fp = fopen("input/day06.txt", "r");
    fscanf(fp, "%s", buffer);
    fclose(fp);

    //printf("%s", buffer);

    // part 1
    //packet_detector(buffer, 4);

    // part 2
    packet_detector(buffer, 14);

}