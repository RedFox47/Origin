/*
	Copyright 2010, Sumeet Chhetri

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
/*
 * AMEFObject.cpp
 *
 *  Created on: Mar 7, 2011
 *      Author: chhetri.sumeet
 */

#include "AMEFObject.h"
#include "iostream"


AMEFObject::~AMEFObject() {
	//cout << packets.size() << endl;
	for (int var = 0; var < (int)packets.size(); var++) {
		AMEFObject *ob = packets.at(var);
		delete ob;
	}
	clear();
}
