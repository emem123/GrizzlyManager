/*
 * macros.h
 *
 *  Created on: Mar 7, 2014
 *      Author: visio
 */

#ifndef MACROS_H_
#define MACROS_H_

#define FOR_RANGE(A, B) for(int n = A; n < B; n++)
#define FOR(FROM,TO,N) for(int N = FROM; N < TO; N++)
#define FOR_EACH(TYPE, S) TYPE::iterator it; \
	for(it = S.begin(); it != S.end(); it++)


#endif /* MACROS_H_ */
