/*
 * browserView.h
 *
 *  Created on: Apr 16, 2010
 *      Author: alx
 */

#ifndef BROWSERVIEW_H_
#define BROWSERVIEW_H_

/**************************************************
 * GET FUNCTIONS
 **************************************************/
char* getAppName(int index);

/**************************************************
 * SET FUNCTIONS
 **************************************************/
void putApp(char*); //The freasy class can add apps to the list via this function
void putInfoScreen(Screen*); //Add info-screens to the view TODO

#endif /* BROWSERVIEW_H_ */
