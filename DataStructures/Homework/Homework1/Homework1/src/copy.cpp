#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>





void flush_right(std::vector<std::vector<std::string>> vec, std::string outfile, int width)
{
    std::ofstream file;
    file.open(outfile);
    //Creates the first and last bar of  "----"
    std::string firstnlast;
    for (int i = 0; i < width + 4; i++)
    {
        firstnlast.append("-");
    }
    file << firstnlast << std::endl;

    //Cycles through the vector of vectors
    for (std::vector<std::string> a : vec)
    {
        std::string line;

        //Cycles through the vector of strings and adds each word to a temp line
        for (std::string b : a)
        {
            line.append(b);
            line.append(" ");


        }
        //takes off the last space and prints 
        line.pop_back();
        file << "| " << std::setw(width) << line << " |" << std::endl;

    }
    file << firstnlast << std::endl;

}

void flush_left(std::vector<std::vector<std::string>> vec, std::string outfile, int width)
{

    std::ofstream file;
    file.open(outfile);
    //Creates the first and last bar of  "----"
    std::string firstnlast;
    for (int i = 0; i < width + 4; i++)
    {
        firstnlast.append("-");
    }
    file << firstnlast << std::endl;

    //Cycles through the vector of vectors
    for (std::vector<std::string> a : vec)
    {
        std::string line;

        //Cycles through the vector of strings and adds each word to a temp line
        for (std::string b : a)
        {
            line.append(b);
            line.append(" ");


        }
        //takes off the last space and prints 
        line.pop_back();
        int fill = width - (line.size() - 2);
        file << "| " << line << std::setw(fill) << " |" << std::endl;

    }
    file << firstnlast << std::endl;

}

void full_justify(std::vector<std::vector<std::string>> vec, std::string outfile, int width)
{

    std::ofstream file;
    file.open(outfile);
    //Creates the first and last bar of  "----"
    std::string firstnlast;
    for (int i = 0; i < width + 4; i++)
    {
        firstnlast.append("-");
    }
    file << firstnlast << std::endl;

    //Cycles through the vector of vectors
    for (std::vector<std::string> a : vec)
    {

        //gets the number of spaces inbetween 
        std::string line;
        int total_size = 0;
        int num_space = a.size() - 1;

        //Finds the total size of the line
        for (std::string c : a)
        {
            total_size += c.size();
        }



        int first = 0;
        int second = 0;

        //finds the average spaces per inbetween 
        double avg = (double)(width - total_size + 0.0) / num_space;
        //if there is only one word on the line
        if (num_space == 0)
        {
            double avg1 = (double)(width - total_size + 0.0) / 2;
            if (avg1 != trunc(avg1))
            {
                first = trunc(avg1) + 1;
                second = first - 1;
            }
            else
            {
                first = int(avg1);
                second = int(avg1);
            }
        }
        //if the avg is not an int value
        else if (avg != trunc(avg))
        {
            first = trunc(avg) + 1;
            second = first - 1;
        }
        else
        {
            first = int(avg);
            second = int(avg);
        }

        //finds the amount of times the bigger of the two spaces should be used
        int remain = (width - total_size) - (second * num_space);
        int runthrough = 0;

        //Cycles through the vector of strings and adds each word to a temp line as well as spaces
        for (std::string b : a)
        {
            //adds spaces to begining if one word
            if (num_space == 0)
            {
                std::string space;
                for (int i = 0; i < first; i++) space.append(" ");
                line.append(space);
                runthrough = remain;
            }
            //adds word
            line.append(b);
            line.append(" ");
            //adds the bigger of the two space values
            if (runthrough < remain)
            {
                std::string space;
                for (int i = 0; i < first - 1; i++) space.append(" ");
                line.append(space);
            }
            //adds the smaller of the two space values
            else if ((runthrough < num_space) && (runthrough >= remain))
            {
                std::string space;
                for (int i = 0; i < second - 1; i++) space.append(" ");
                line.append(space);
            }
            runthrough++;

        }
        //takes off the last space and prints 
        line.pop_back();
        file << "| " << line << " |" << std::endl;

    }
    file << firstnlast << std::endl;

}


int main(int argc, char* argv[])
{
    // Read in the information
    //std::cout << "Enter the input file, output file, width of box, and orientation: " << std::endl;

    std::string infile = std::string(argv[1]);
    std::string outfile = std::string(argv[2]);
    std::string orientation = std::string(argv[4]);
    unsigned int width = atoi(argv[3]);
    //std::cin >> infile, std::cin >> outfile, std::cin >> width, std::cin >> orientation;
    std::cout << "bill";

    //Reads the file and puts into vector
    std::vector<std::string> words;
    std::string w;
    std::ifstream myfile(infile);
    if (myfile.is_open())
    {
        while (myfile >> w)
        {
            words.push_back(w);
        }
        myfile.close();
        std::cout << "File successfully opened" << std::endl;
    }
    else std::cerr << "Unable to open file" << std::endl;

    /*
    Summary of what my program does
    To split the words up, I created two vectors, one for storing the words that will be on one line (tempvec) as it will be cleared alot,
    the second is the vector of vectors called main, and in each position of the vector there is a new line in the text box. I check the words
    length to a width variable that decreases with everyword added, by that size. For words that are too big, the program splits it up and
    runs a while loop until the the split word is not greater than the width given. To make the actual textbox, I passed the vector of
    vectors (main) into my function which would read the vector of strings one at a time and will process them and put them into a the output
    file
    */



    //creates the vector of vectors and the vectors of strings
    std::vector<std::vector<std::string>> main;
    std::vector<std::string> tempvec;
    unsigned int tempwidth = width;

    //runs through the words
    for (std::string word : words)
    {
        //will split the word into two
        if (word.size() > width)
        {
            //checks to see if tempvec is empty before putting on main vector
            if (tempvec.size() != 0)
            {
                main.push_back(tempvec);
                tempvec.clear();
            }
            //splitting of the word and adding it to the main vector
            while (word.size() > width)
            {

                std::string newword;

                newword = word.substr(0, (width - 1));
                newword.append("-");
                word = word.substr(width - 1, word.size() - 1);
                tempvec.push_back(newword);

                main.push_back(tempvec);
                tempvec.clear();
                tempwidth = width;
            }
            // adds the residual of the split word
            tempvec.push_back(word);
            tempwidth -= word.size();

        }
        //adds word to the vector of springs
        else if (word.size() + 1 < tempwidth)
        {
            tempvec.push_back(word);
            tempwidth -= word.size() + 1;
        }
        //adds the vector of words to the main vector
        else
        {
            main.push_back(tempvec);
            tempvec.clear();
            tempvec.push_back(word);
            tempwidth = width - word.size() + 1;

        }

    }
    main.push_back(tempvec);

    //  checks the vector of vectors
   /*
    for (std::vector<std::string> a : main)
    {
        for (std::string b : a)
        {
            std::cout << b << " ";
        }
        std::cout << std::endl;
    }
    */

    if (orientation == "flush_right")
    {

        flush_right(main, outfile, width);
    }
    else if (orientation == "flush_left")
    {

        flush_left(main, outfile, width);
    }
    else if (orientation == "full_justify")
    {

        full_justify(main, outfile, width);
    }
    else
    {
        std::cerr << "Incorrect input" << std::endl;
    }

}