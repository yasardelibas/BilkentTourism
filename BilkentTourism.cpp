    //Yaşar Delibaş 22302530 Section 03
    
    
    #include "BilkentTourism.h"


    //Constructor
    BilkentTourism::BilkentTourism(){
        headBusLines = nullptr;
        headAllStops = nullptr;
    }

    //Destructor

    BilkentTourism::~BilkentTourism()
    {
        //Delete all busLines, stops, busses

        BusLineNode* currentLine = headBusLines;

        while(currentLine != nullptr)
        {
            BusLineNode* tempLine = currentLine;

            //Deleting all stops
            StopNode* currStop = currentLine->stopsHead;

            while(currStop != nullptr)
            {
                StopNode* tempStop =  currStop;
                currStop = currStop->next;
                delete tempStop;
            }

            //Deleting all busses assigned on line

            BusNode* currBus = currentLine->bussesHead;

            while(currBus != nullptr)
            {
                BusNode* tempBus = currBus;
                currBus = currBus->next;
                delete tempBus;
            }

            currentLine = currentLine->next;
            delete tempLine;
        }


        //Delete the list of stops

        StopNode* curMasterStop = headAllStops;
        while(curMasterStop != nullptr)
        {
            StopNode* temp = curMasterStop;
            curMasterStop = curMasterStop->next;
            delete temp;
        }
    }
    //Copy Constructor
    BilkentTourism::BilkentTourism(const BilkentTourism& other)
    {
        headBusLines = nullptr;
        headAllStops = nullptr;

        //Copy headAllStops

        if(other.headAllStops != nullptr)
        {
            headAllStops = new StopNode(other.headAllStops->id, other.headAllStops->stopName);

            StopNode* srcPtr = other.headAllStops->next;
            StopNode* destPtr = headAllStops;

            while(srcPtr != nullptr)
            {
                destPtr->next = new StopNode(srcPtr->id, srcPtr->stopName);
                destPtr = destPtr->next;
                srcPtr = srcPtr->next;
            }
            //Copy BusLines
            if(other.headBusLines != nullptr)
            {
                headBusLines = new BusLineNode(other.headBusLines->id, other.headBusLines->name);

                BusLineNode* srcLine = other.headBusLines;
                BusLineNode* destLine = headBusLines;


                while(srcLine != nullptr)
                {
                    //Copy stops inside line

                    if(srcLine->stopsHead != nullptr)
                    {
                        destLine->stopsHead = new StopNode(srcLine->stopsHead->id,srcLine->stopsHead->stopName);
                        StopNode* sSrc = srcLine->stopsHead->next;
                        StopNode* sDest = destLine->stopsHead;

                        while(sSrc != nullptr)
                        {
                            sDest->next = new StopNode(sSrc->id, sSrc->stopName);
                            sDest = sDest->next;
                            sSrc = sSrc->next;
                        }
                    }
                    else{
                        destLine->stopsHead = nullptr;
                    }


                    if(srcLine->bussesHead != nullptr)
                    {
                        destLine->bussesHead = new BusNode(srcLine->bussesHead->id, srcLine->bussesHead->driverName);
                        BusNode* bSrc = srcLine->bussesHead->next;
                        BusNode* bDest = destLine->bussesHead;

                        while(bSrc != nullptr)
                        {
                            bDest->next = new BusNode(bSrc->id, bSrc->driverName);
                            bDest = bDest->next;
                            bSrc = bSrc->next;
                        }
                    }else{
                        destLine->bussesHead= nullptr;
                    }

                    if(srcLine->next != nullptr)
                    {
                        destLine->next = new BusLineNode(srcLine->next->id, srcLine->next->name);
                        destLine = destLine->next;
                        srcLine = srcLine->next;
                    }
                    else{
                        destLine->next = nullptr;
                        srcLine = nullptr;
                    }
                }
            }
        }
    }

    void BilkentTourism::addBusLine( const int lineId, const string lineName )
    {
        //Checking if the ID is available
        BusLineNode* cur = headBusLines;

        while(cur != nullptr)
        {
            if(cur->id == lineId)
            {
                cout<< "Cannot add line. There is already a bus line with ID " << lineId << "." <<endl;
                return;
            }
            cur= cur->next;
        }

        //Creating the new node to add
        BusLineNode* newNode = new BusLineNode(lineId, lineName);

        //The list is empty or the new id is smaller than the head id
        //The insertion is at the beginning

        if(headBusLines == nullptr || headBusLines->id > lineId)
        {
            newNode->next = headBusLines;
            headBusLines = newNode;
        }
        else{ //Inserting busLine apart from head
            cur = headBusLines;
            //Examining each and every node to find the exact spot to insert
            while(cur->next != nullptr && cur->next->id < lineId)
            {
                cur = cur->next;
            }

            newNode->next = cur->next;
            cur->next = newNode;
        }

        cout<< "Added bus line " << lineId << "." << endl;
    }

    void BilkentTourism::printBusLines() const{
        //Checking if list is empty
        if(headBusLines == nullptr)
        {
            cout << "There are no bus lines to show." << endl;
            return;
        }

        cout << "Bus lines in the system:" << endl;

        //Traverse the list and print the busLines
        BusLineNode* cur = headBusLines;

        while(cur != nullptr)
        {
            cout << "Line " << cur->id << " : " << cur->name<< endl;
            cur= cur->next;
        }
    }

    void BilkentTourism::removeBusLine( const int lineId ){

        //Finding the node and the prev
        BusLineNode* curr = headBusLines;
        BusLineNode* prev = nullptr;

        while(curr!= nullptr && curr->id != lineId)
        {
            prev = curr;
            curr = curr->next;
        }

        //Line is not found
        if(curr == nullptr)
        {
            cout <<"Cannot remove bus line. There is no bus line with ID "<< lineId << "." << endl;
            return;
        }

        //Line is found and deleting all other lists inside busLine
        StopNode* sHead = curr->stopsHead;
        while(sHead != nullptr)
        {
            StopNode* temp = sHead;
            sHead = sHead->next;
            delete temp;
        }

        //Deleting busses
        BusNode* bHead = curr->bussesHead;
        while(bHead != nullptr)
        {
            BusNode* temp = bHead;
            bHead = bHead->next;
            delete temp;
        }

        if(prev == nullptr)
        {
            //If at the beginning
            headBusLines = curr->next;
        }
        else{
            //Removing the busLine
            prev->next = curr->next;
        }

        //Deleting the curr since we successfully linked the list
        delete curr;

        cout<< "Removed bus line " << lineId << "." << endl;
    }

    //Stop operations
    void BilkentTourism::addStop(const int stopId, const string stopName)
    {
        //Checking the existance
        StopNode* curr = headAllStops;
        while(curr!= nullptr)
        {
            if(curr->id == stopId)
            {
                cout<< "Cannot add stop. BilkentTourism already contains stop " << stopId << "." << endl;
                return;
            }
            curr= curr->next;
        }

        //Creating the newStopNode
        StopNode* newStop = new StopNode(stopId, stopName);

        //Inserting at the end of the stop list(empty or new Id is smaller than headStop id)
        if(headAllStops == nullptr || headAllStops->id > stopId)
        {
            newStop->next = headAllStops;
            headAllStops = newStop;
        }
        else{
            curr =  headAllStops;
            while(curr->next != nullptr && curr->next->id < stopId)
            {
                curr = curr->next;
            }

            newStop->next = curr->next;
            curr->next = newStop;
        }

        cout<< "Added stop " << stopId<< "." << endl;
    }

    void BilkentTourism::removeStop(const int stopId)
    {
        //Check if the stop exists in the list

        StopNode* curr = headAllStops;
        StopNode* prev = nullptr;
        
        bool found = false;

        while(curr!=nullptr)
        {
            if(curr->id == stopId)
            {
                found = true;
                break;
            }
            prev = curr;
            curr= curr->next;
        }

        if(!found)
        {
            cout<<"Cannot remove stop " << stopId << ". There is no bus stop with ID " << stopId << "." << endl;
            return;
        }

        //Checking the bus stop currently used in any bus Line
        BusLineNode* lineCurr = headBusLines;
        while(lineCurr != nullptr)
        {
            StopNode* sCurr = lineCurr->stopsHead;

            while(sCurr != nullptr)
            {
                if(sCurr->id == stopId)
                {
                    cout<< "Cannot remove stop " << stopId << ". The stop is currently in use." << endl;
                    return; 
                }
                sCurr = sCurr->next;
            }

            lineCurr = lineCurr->next;
        }

        //Remove from the list
        if(prev == nullptr)
        {
            headAllStops = curr->next;
        }
        else{
            prev->next = curr->next;
        }

        delete curr;

        cout<< "Removed stop " << stopId<< "." << endl;
    }

    void BilkentTourism::addStopToLine(const int stopId, const int lineId)
    {
        //Find the bus line
        BusLineNode* lineCurr = headBusLines;

        while(lineCurr != nullptr && lineCurr->id !=lineId)
        {
            lineCurr = lineCurr->next;
        }

        //Find the stop from the list
        StopNode* masterStop = headAllStops;
        while(masterStop != nullptr && masterStop->id != stopId)
        {
            masterStop = masterStop->next;
        }

        //Checking the stop is existing or not
        if(masterStop == nullptr)
        {
            cout<< "Cannot add stop. There is no stop with ID " << stopId << "." << endl;
            return;
        }

        if(lineCurr == nullptr)
        {
            cout<< "Cannot add stop. There is no line with ID " << lineId << "." << endl;
            return;
        }

        //Check if the stop is already on the line
        StopNode* lineStopCurr = lineCurr->stopsHead;

        while(lineStopCurr != nullptr)
        {
            if(lineStopCurr->id == stopId)
            {
                cout << "Cannot add stop. Line " << lineId << " already contains stop " << stopId << "." << endl;
                return;
            }
            lineStopCurr = lineStopCurr->next;
        }

        //Creating new stopNode
        StopNode* newStop = new StopNode(stopId, masterStop->stopName);

        //Insert into line
        if(lineCurr-> stopsHead == nullptr || lineCurr->stopsHead->id > stopId)
        {
            newStop->next = lineCurr-> stopsHead;
            lineCurr-> stopsHead = newStop;
        }
        else{
            lineStopCurr = lineCurr->stopsHead;
            while(lineStopCurr->next != nullptr && lineStopCurr->next->id < stopId)
            {
                lineStopCurr = lineStopCurr->next;
            }
            
            newStop->next = lineStopCurr->next;
            lineStopCurr-> next = newStop;
        }

        cout << "Added stop " << stopId << " to line " << lineId << " (" << lineCurr->name << ")." << endl;
    }

    void BilkentTourism::removeStopFromLine(const int stopId, const int lineId)
    {
        BusLineNode* lineCur = headBusLines;

        while(lineCur!= nullptr && lineCur->id != lineId)
        {
            lineCur = lineCur->next;
        }

        if(lineCur == nullptr)
        {
            cout << "Cannot remove stop. There is no line with ID " << lineId << "." << endl;
            return;
        }

        //Find the stop in the specific line
        StopNode* curr = lineCur->stopsHead;
        StopNode* prev = nullptr;

        while(curr != nullptr && curr->id != stopId)
        {
            prev = curr;
            curr = curr->next;
        }

        //Stop not found case
        if(curr == nullptr){
            cout << "Cannot remove stop. Line " << lineId << " does not have stop " << stopId << "." << endl;
            return;
        }

        //Delete the stop from the line
        if(prev == nullptr)
        {
            lineCur->stopsHead = curr->next;
        }
        else{
            prev->next = curr->next;
        }

        delete curr;
        cout << "Removed stop " << stopId << " from line " << lineId << "." << endl;
    }


    void BilkentTourism::printStops(const int lineId) const {
        //Find the bus line
        BusLineNode* lineCurr = headBusLines;

        while(lineCurr != nullptr && lineCurr->id != lineId)
        {
            lineCurr = lineCurr->next;
        }


        if(lineCurr == nullptr)
        {
            cout << "Cannot print stops. There is no line with ID " << lineId << "." << endl;
            return;
        }

        //Check if line have some stops

        if(lineCurr->stopsHead == nullptr)
        {
            cout << "Cannot print stops. There is no stop to show." << endl;
            return;
        }

        //Print stops
        cout << "Stops in bus line " << lineId << " (" << lineCurr->name << ") :" << endl;
        StopNode* curr = lineCurr->stopsHead;

        while(curr!= nullptr){
            cout << "Stop " << curr->id << " : " << curr->stopName << endl;
            curr = curr->next;
        }
    }

    void BilkentTourism::assignBus(const int busId, const string driverName, const int lineId)
    {
        //Check if the line exists
        BusLineNode* targetLine = headBusLines;

        while(targetLine != nullptr && targetLine->id != lineId)
        {
            targetLine = targetLine->next;
        }

        if(targetLine == nullptr)
        {
            cout << "Cannot assign bus. There is no line with ID " << lineId << "." << endl;
            return;
        }

        //Is this bus ID already used in any line
        BusLineNode* currLine = headBusLines;

        while(currLine != nullptr)
        {
            BusNode* currBus = currLine->bussesHead;
            
            while(currBus != nullptr)
            {
                if(currBus->id == busId)
                {
                    cout << "Cannot assign bus. Bus " << busId << " is already assigned to a line." << endl;
                    return;
                }
                currBus = currBus->next;
            }

            currLine = currLine->next;
        }

        //Create newBusNode
        BusNode* newBus = new BusNode(busId, driverName);

        //Insert the newBus in an ascending order
        if(targetLine->bussesHead == nullptr || targetLine->bussesHead->id > busId)
        {
            newBus->next = targetLine->bussesHead;
            targetLine->bussesHead = newBus;
        }
        else
        {
            BusNode* curr = targetLine->bussesHead;

            while(curr->next != nullptr &&  curr->next->id < busId)
            {
                curr = curr->next;
            }

            newBus->next = curr->next;
            curr->next = newBus;
        }

        cout << "Bus " << busId << " with driver " << driverName << " is assigned to line " << lineId << " (" << targetLine->name << ")." << endl;

    }

    void BilkentTourism::unassignBus(const int busId)
    {
        //Search all lines
        BusLineNode* currLine = headBusLines;

        while(currLine != nullptr)
        {
            BusNode* currBus = currLine->bussesHead;
            BusNode* prevBus = nullptr;

            while(currBus != nullptr)
            {
                if(currBus->id == busId)
                {
                    //Found it and remove it
                    if(prevBus == nullptr)
                    {
                        currLine->bussesHead = currBus->next;
                    }
                    else{
                        prevBus->next = currBus->next;
                    }

                    cout << "Bus " << busId << " is unassigned from line " << currLine->id << " (" << currLine->name << ")." << endl;

                    delete currBus;
                    return;
                }

                prevBus = currBus;
                currBus = currBus->next;
            }
            currLine = currLine->next;
        }
        cout << "Cannot unassign bus. There is no bus with ID " << busId << "." << endl;
    }

    void BilkentTourism::printBussesInLine(const int lineId) const{
        //Find the line
        BusLineNode* currLine = headBusLines;

        while(currLine != nullptr && currLine->id != lineId)
        {
            currLine = currLine->next;
        }

        if(currLine == nullptr)
        {
            cout << "Cannot print busses. There is no line with ID " << lineId << "." << endl;
            return;
        }

        //check if the bus exists
        if(currLine->bussesHead == nullptr)
        {
            cout << "There are no bus to show in line " << lineId << " (" << currLine->name << ")." << endl;
            return;
        }

        cout << "Busses and their drivers assigned to the line " << lineId << " (" << currLine->name << "):" << endl;
        BusNode* currBus = currLine->bussesHead;

        while(currBus != nullptr)
        {
            cout << "Bus " << currBus->id << " : " << currBus->driverName << endl;
            currBus = currBus->next;
        }

    }

    void BilkentTourism::printBussesPassingStop(const int stopId) const {
        //Check the stop is exists in the list or not

        StopNode* sCurr = headAllStops;
        bool stopExists = false;

        while(sCurr != nullptr)
        {
            if(sCurr->id == stopId)
            {
                stopExists = true;
                break;
            }
            sCurr = sCurr->next;
        }

        if(!stopExists)
        {
            cout << "Cannot print buses. There is no stop with ID " << stopId << "." << endl;
            return;
        }

        int passingLinesCount = 0;
        BusLineNode* lines = headBusLines;

        while(lines != nullptr)
        {
            StopNode* stops = lines->stopsHead;

            while(stops != nullptr)
            {
                if(stops->id == stopId)
                {
                    passingLinesCount++;
                    break;
                }
                stops = stops->next;
            }
            lines = lines->next;
        }

        if(passingLinesCount == 0)
        {
            cout << "Cannot print buses. No lines pass through the stop." << endl;
            return;
        }

        //print output
        string stopName = sCurr->stopName;
        cout << "Buses and their assigned lines passing the stop " << stopId << " (" << stopName << "):" << endl;

        BusLineNode* currLine = headBusLines;

        while(currLine != nullptr)
        {
            bool hasStop = false;

            StopNode* stopCheck = currLine->stopsHead;

            while(stopCheck != nullptr)
            {
                if(stopCheck->id == stopId)
                {
                    hasStop = true;
                    break;
                }
                stopCheck = stopCheck->next;
            }


            if(hasStop)
            {
                cout << "Line " << currLine->id << " (" << currLine->name << ") : ";

                //Print bus id's in [ order ]

                BusNode* bCurr = currLine->bussesHead;

                if(bCurr == nullptr)
                {
                    cout << "None" << endl;
                }
                else
                {
                    cout << "[";
                    
                    while(bCurr != nullptr)
                    {
                        cout << bCurr->id;
                        
                        if(bCurr->next !=nullptr)
                        {
                            cout << ",";
                        }

                        bCurr = bCurr->next;
                    }
                    cout << "]" << endl;
                }
            }
            currLine = currLine->next;
        }
    }
