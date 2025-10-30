/**
 * @file testing.cpp
 * @brief This script compares the original dataset files with 
 * the decrypted files. 
 * @author Iole Bolognesi
 * 
 * This script executes a function that compares, byte-by-byte, 
 * the files with the same name within two different directories.
 * It reports a successful outcome if the contents of all corresponding files match. 
 */

#include <iostream>
#include <filesystem>
#include <fstream>

/**
 * @brief Verifies that original dataset files correspond to decrypted files.
 *
 * This function performs a binary, byte-by-byte comparison between each file in the
 * specified `dataset_directory` and the file with the same name in `decryption_path`.
 * It is used to verify the correctness of the serial or parallel pipeline by 
 * testing if the decrypted files are identical to the originals dataset files. .
 *
 * @param dataset_directory Path to the directory containing the original dataset files.
 * @param decryption_path   Path to the directory containing the decrypted files.
 * @return true  If all corresponding files in the two directories match;
 *         false If one or more files differ.
 */
bool checkCorrectness(const std::filesystem::path dataset_directory,
                    const std::filesystem::path decryption_path){

    bool success=true;


    for (const auto& entry : std::filesystem::directory_iterator{dataset_directory}) {

        std::cout << "Checking file " << entry.path().filename().string() <<std::endl; 
        
        const std::string file1 = entry.path().string();
        const std::string file2 = (decryption_path / entry.path().filename()).string();

        std::ifstream f1(file1, std::ios::binary);
        std::ifstream f2(file2, std::ios::binary);

        std::istreambuf_iterator<char> begin1(f1), end1;
        std::istreambuf_iterator<char> begin2(f2), end2;
        

        if(!std::equal(begin1, end1, begin2, end2)){
            std::cout <<"Files " << entry.path().filename().string() << " differ" <<std::endl;
            success=false;
        }
    
    }

    return success;
}

int main(int argc, char *argv[]) {

    std::string dir1 = argv[1]; 
    std::string dir2 = argv[2]; 
    const std::filesystem::path data_path{dir1};
    const std::filesystem::path decryption_output_path{dir2};

    bool success = checkCorrectness(data_path,decryption_output_path);

    if (success){
        std::cout<< "The program encrypted and stored the" <<
                    " dataset correctly "<<std::endl;
    }

}