//Yaşar Delibaş 22302530 Section 03

#ifndef BILKENTTOURISM_H
#define BILKENTTOURISM_H

#include <string>
#include <iostream>

using namespace std;


class BilkentTourism{

    private:

        //The Bus Node
        struct BusNode{
            int id;
            string driverName;
            BusNode* next;

            BusNode(int i, string d){
                this->id = i;
                this->driverName = d;
                this->next = nullptr;
            }
        };

        //The Stop Node
        struct StopNode{
            int id;
            string stopName;
            StopNode* next;

            StopNode(int i, string n)
            {
                this->id = i;
                this->stopName = n;
                this->next = nullptr;
            }
        };

        //The Bus Line Node
        struct BusLineNode{
            int id;
            string name;

            //Pointers to lists

            StopNode* stopsHead;
            BusNode* bussesHead;

            BusLineNode* next;

            BusLineNode(int i, string n)
            {
                this->id = i;
                this->name = n;
                stopsHead = nullptr;
                bussesHead = nullptr;
                next = nullptr;
            }
        };

        //Head of Bus lines (sorted)
        BusLineNode* headBusLines;
        StopNode*   headAllStops;
        
    public:
        //Constructor and destructor
        BilkentTourism();
        ~BilkentTourism();

        BilkentTourism(const BilkentTourism& other); // Copy constructor
        
        //BusLine operations
        void addBusLine( const int lineId, const string lineName );
        void removeBusLine( const int lineId );
        void printBusLines() const;

        //Stop operations
        void addStop( const int stopId, const string stopName );
        void removeStop( const int stopId);
        void addStopToLine( const int stopId, const int lineId);
        void removeStopFromLine( const int stopId, const int lineId);
        void printStops( const int lineId ) const;

        //Bus operations
        void assignBus( const int busId, const string driverName, const int lineId);
        void unassignBus( const int busId);
        void printBussesInLine( const int lineId) const;
        void printBussesPassingStop( const int stopId) const;

    };
        
#endif