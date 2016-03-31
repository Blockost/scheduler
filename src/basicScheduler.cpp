//
// Created by hugo on 31/03/16.
//

#include "basicScheduler.h"

/**
 * \file    basicScheduler.cpp
 * \author  Simon ESPIGOLÉ, Teddy GILBERT, Hugo LEGRAND
 * \version 1.0
 * \date    03/31/16
 * \brief   Runs the basic scheduler strategy
 * \details This class reads the JSON file in input, populates the pool, and affects each task to a processor.
 */

/**
 * \brief   Runs the scheduler
 * \param   argc Number of arguments passed
 * \param   argv Arguments passed
 * \return  0 if everything is OK, -1 if not.
 */
int BasicScheduler(int argc, char** argv) {
    /* Checking number of arguments */
    if (argc != 1) {
        cout << "BasicScheduler : You need to supply only one argument to this program.";
        return -1;
    }

    /* Checking if the file exists, and if JSON and well constructed */
    if (!boost::filesystem::exists(argv[0])) {
        cout << "BasicScheduler : File " << argv[0] << "does not exist.";
        return -1;
    }else{
        /* Importing JSON */

        return 1;
    }
}