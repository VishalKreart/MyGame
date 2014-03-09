/*
 * StoreController.h
 *
 *  Created on: Nov 19, 2013
 *      Author: Vikas Patidar
 */

#ifndef STORECONTROLLER_H_
#define STORECONTROLLER_H_

class StoreController {
public:
	StoreController();
	virtual ~StoreController();

	static void buyItem(const char* itemId);
	static void restore();

	static void openStore(void);
	static void closeStore(void);

	static bool m_bIsStoreInitialized;
	static bool m_bIsRunning;
};

#endif /* STORECONTROLLER_H_ */
