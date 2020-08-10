/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: yael
 *
 * Created on May 30, 2019, 2:17 PM
 */

#include "speak.hpp"

/**
 * the testing main
 */
int main() {
    Lily::speak::synthesize(
            "Hallo Welt, wie geht es dir(lang:mb-de6)");

    return 0;

}
