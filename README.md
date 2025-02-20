# Project 1: Encryption Algorithm

        Encryption:

        This encryption algorithm takes input from a .txt file using <fstream> and reads it into a string
        variable. This string variable is then parsed into seperate char variables "Insert here how you handle
        spaces and symbols" and stored in a vector. n represents the square root of the number of char varialbes
        in the plain text message exluding spaces. In the event that a message contains an amount of char
        variables that is not a perfect square root 0's are inserted until the size of the vector is a perfect
        square root. The char variables are then inserted into a two dimensional array simulating an nxn matrix.
        This is matrix is then transposed and each variable is shifted either left or right depending on if the
        column is even or odd (0's will be ignored). The encrypted variables are now put back into a vector and
        then converted into a string variable "Put explanation here of how you handled the spaces" which is sent
        out to a .txt file.

        Decryption:

        The decryption is the reverse of the encyrption algorithm, first the encrypted message is read in from a
        .txt file and stored in a string variable. This message is then parsed into char variables stored in a
        vector. The vector is then put into a two dimensional array of size nxn. The nxn matrix is then
        transposed and the the inverse shift operators from the encryption is done depending on if the current
        column is even or odd (0's will be ignored). The char variables are then put back into a vector and then
        converted into a string variable "Explain how you handled spaces" that is then sent out to a .txt file.

# Instructions

        The menu:
