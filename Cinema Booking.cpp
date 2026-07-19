#include <iostream>
#include <string>
#include <queue>
#include <list>
using namespace std;

const int  ticket_price= 30000;
const int food_price[]={65000, 38000, 43000, 32000, 55000};
const int drink_price[]={32000,32000, 32000, 37000, 50000, 30000, 65000};
const string SHOWTIME_DESCRIPTION[] = {"12:25", "14:20", "16:15", "18:10", "20:05"};
const int NUM_SHOWTIMES = sizeof(SHOWTIME_DESCRIPTION) / sizeof(SHOWTIME_DESCRIPTION[0]);
const int NUM_choiceMovie = 5;
const string MovieChoices[] = {
    "The SpongeBob Movie: Sponge on the Run",
    "One Piece Film: Red",
    "Tom and Jerry: Snowman's Land",
    "Doraemon The Movie: Nobita's Little Star Wars 2021",
    "Sofia The First: The Buttercups"};
const string FoodsOrder[] = {
    "Popcorn",
    "French Fries",
    "Mac and Cheese",
    "Nachos",
    "Mini Fried Dumpling"};
const int NUM_ordersfood =sizeof(FoodsOrder) / sizeof(FoodsOrder[0]);
const string DrinksOrder[] = {
       "Coca-Cola",
	   "Fanta",
	   "Sprite",
	   "Lemon Tea",
	   "Milo Dinosaurus",
	   "Java Tea Special",
	   "Lychee Tea"};
const int NUM_ordersdrink = sizeof(DrinksOrder) / sizeof(DrinksOrder[0]);

struct Customer {
    string name;
    list<int> drinkOrders;
    list<int> foodOrders;
    int foodPayment,drinkPayment,ticketPayment,showtimeChoice, movieChoice, foodChoice, foodQuantity, drinkQuantity,drinkOrder = 0,foodOrder = 0,ticketOrder=0;
    string seatNumber,SHOWTIME_DESCRIPTION;

    Customer() : ticketPayment(0), foodPayment(0), drinkPayment(0) {}
};

struct Node {
    Customer customerInfo;
    Node* next;
    bool deleted;
    Node() : next(nullptr), deleted(false) {}
};


class QueueBase {
public:
    virtual void enqueue(Customer customer) = 0;
    virtual void dequeue() = 0;
    virtual void displayQueue() const = 0;
    virtual void displayRemovedData() const = 0;
    virtual ~QueueBase() {}  
};

class TicketQueue : public QueueBase {
private:
    queue<Node*> ticketQueue;
    queue<Node*> tempQueue;

public:
    void enqueue(Customer customer) override {
        Node* newNode = new Node;
        newNode->customerInfo = customer;
        newNode->next = nullptr;

        if (ticketQueue.empty()) {
            ticketQueue.push(newNode);
        } else {
            Node* rear = ticketQueue.back();
            rear->next = newNode;
            ticketQueue.push(newNode);
        }
        cout << "\nData has been input.\n\n";
    }

    void dequeue() override {
        if (ticketQueue.empty()) {
            cout << "Ticket queue is empty.\n\n";
        } else {
            Node* removedCustomer = ticketQueue.front();
            ticketQueue.pop();
            cout << "Customer " << removedCustomer->customerInfo.name << " has been removed from queue.\n\n";
			removedCustomer->deleted = true;
            tempQueue.push(removedCustomer);
        }
    }

    void displayQueue() const override {
        if (ticketQueue.empty()) {
            cout << "Ticket queue is empty.\n\n";
        } else {
            Node* current = ticketQueue.front();
            while (current != nullptr) {
                cout << "\nName: " << current->customerInfo.name << endl;
                cout << "Movie Choice : " << getMovieChoice(current->customerInfo.movieChoice) << endl;
                cout << "Ticket Quantity : " << current->customerInfo.ticketOrder << endl;
                cout << "Movie Time : " << getShowtimeDescription(current->customerInfo.showtimeChoice) << endl;
                cout << "Total Payment: " << current->customerInfo.ticketOrder * ticket_price << endl;

                current = current->next;
            }
        }
        cout << endl;
    }
    
	string getMovieChoice(int movieChoice) const {
   		if (movieChoice >= 1 && movieChoice <= NUM_choiceMovie) {
    		return MovieChoices[movieChoice - 1];
    	} else {
        	return "Unknown MovieChoice";
    	}
  	}
  	
  	string getShowtimeDescription(int showtimeChoice) const {
        if (showtimeChoice >= 1 && showtimeChoice <= NUM_SHOWTIMES) {
            return SHOWTIME_DESCRIPTION[showtimeChoice - 1];
        } else {
            return "Unknown Showtime";
        }
    }
  	
    void displayRemovedData() const {
        if (tempQueue.empty()) {
            cout << "No data has been removed.\n\n";
        } else {
            Node* current = tempQueue.front();
            cout << "Deleted Order :\n";
            while (current != nullptr) {
            	if (current->deleted){
            		cout << "\nName: " << current->customerInfo.name << endl;
	                cout << "Movie Choice : " << getMovieChoice(current->customerInfo.movieChoice) << endl;
	                cout << "Ticket Quantity : " << current->customerInfo.ticketOrder << endl;
	                cout << "Movie Time : " << getShowtimeDescription(current->customerInfo.showtimeChoice) << endl;
	                cout << "Total Payment: " << current->customerInfo.ticketOrder * ticket_price << endl;
				}
                current = current->next;
            }
            cout << endl;
        }
    }

    bool hasRemovedData() const {
        return !tempQueue.empty();
    }

    ~TicketQueue() override {
        while (!ticketQueue.empty()) {
            Node* temp = ticketQueue.front();
            ticketQueue.pop();
            delete temp;
        }
        while (!tempQueue.empty()) {
            Node* temp = tempQueue.front();
            tempQueue.pop();
            delete temp;
        }
    }
};


class FoodQueue : public QueueBase {
private:
    queue<Node*> food;
    queue<Node*> tempQueue;

public:
    void enqueue(Customer customer) override {
        Node* newNode = new Node;
        newNode->customerInfo = customer;
        newNode->next = nullptr;

        if (food.empty()) {
            food.push(newNode);
        } else {
            Node* rear = food.back();
            rear->next = newNode;
            food.push(newNode);
        }
        cout << "\nData has been input.\n\n";
    }

    void dequeue() override {
        if (food.empty()) {
            cout << "Food queue is empty.\n\n";
        } else {
            Node* removedCustomer = food.front();
            food.pop();
            cout << "Customer " << removedCustomer->customerInfo.name << " has been removed from queue.\n\n";
            removedCustomer->deleted = true;
			tempQueue.push(removedCustomer);
        }
    }

    void displayQueue() const override {
	    if (food.empty()) {
	        cout << "Order queue is empty.\n\n";
	    } else {
	        Node* current = food.front();
	        while (current != nullptr) {
	            cout << "\nName: " << current->customerInfo.name << endl;
	            cout << "Food Order: " << getFoodsOrder(current->customerInfo.foodOrder) << endl;
	            cout << "Order Quantity: " << current->customerInfo.foodQuantity << endl;
	            int orderIndex = current->customerInfo.foodOrder - 1;
	            cout << "Total Payment: " << food_price[orderIndex] * current->customerInfo.foodQuantity << endl;
	
	            current = current->next;
	        }
	    }
	}

    string getFoodsOrder(int foodOrder) const {
        if (foodOrder >= 1 && foodOrder <= NUM_ordersfood) {
            return FoodsOrder[foodOrder - 1];
        } else {
            return "Unknown Food Order";
        }
    }

    void displayFoodsMenu() const {
        cout << "Foods Menu :\n";
        for (int i = 0; i < NUM_ordersfood; ++i) {
            cout << i + 1 << ". " << FoodsOrder[i] << endl;
        }
        cout << NUM_ordersfood + 1 << ". Cancel" << endl;
    }

   	void cleanupFoodQueue() {
        while (!food.empty()) {
            Node* temp = food.front();
            food.pop();
            delete temp;
        }

        while (!tempQueue.empty()) {
            Node* temp = tempQueue.front();
            tempQueue.pop();
            delete temp;
        }
    }

    ~FoodQueue() override {
        cleanupFoodQueue();
    }
    
    void displayRemovedData() const {
        if (tempQueue.empty()) {
        cout << "No data has been removed.\n\n";
	    } else {
	        Node* current = tempQueue.front();
	        cout << "Deleted Order :\n";
	        while (current != nullptr) {
	        	 if (current->deleted){
	        	 	cout << "\nName: " << current->customerInfo.name << endl;
		            cout << "Food Order: " << getFoodsOrder(current->customerInfo.foodOrder) << endl;
		            cout << "Order Quantity: " << current->customerInfo.foodQuantity << endl;
		            int orderIndex = current->customerInfo.foodOrder - 1;
		            cout << "Total Payment: " << food_price[orderIndex] * current->customerInfo.foodQuantity << endl;
				 }
	            current = current->next;
	        }
	        cout << endl;
	    }
    }
    
    bool hasRemovedData() const {
        return !tempQueue.empty();
    }
};

class DrinkQueue : public QueueBase {
private:
    queue<Node*> drink;
    queue<Node*> tempQueue;

public:
    void enqueue(Customer customer) override {
        Node* newNode = new Node;
        newNode->customerInfo = customer;
        newNode->next = nullptr;

        if (drink.empty()) {
            drink.push(newNode);
        } else {
            Node* rear = drink.back();
            rear->next = newNode;
            drink.push(newNode);
        }
        cout << "\nData has been input.\n\n";
    }

    void dequeue() override {
        if (drink.empty()) {
            cout << "Drink queue is empty.\n\n";
        } else {
            Node* removedCustomer = drink.front();
            drink.pop();
            cout << "Customer " << removedCustomer->customerInfo.name << " has been removed from queue.\n\n";
            removedCustomer->deleted = true;
			tempQueue.push(removedCustomer);
        }
    }

    void displayQueue() const override {
	    if (drink.empty()) {
	        cout << "Order queue is empty.\n\n";
	    } else {
	        Node* current = drink.front();
	        while (current != nullptr) {
	            cout << "\nName: " << current->customerInfo.name << endl;
	            cout << "Drink Order: " << getDrinksOrder(current->customerInfo.drinkOrder) << endl;
	            cout << "Order Quantity: " << current->customerInfo.drinkQuantity << endl;
	            int orderIndex = current->customerInfo.drinkOrder - 1;
	            cout << "Total Payment: " << drink_price[orderIndex] * current->customerInfo.drinkQuantity << endl;
	
	            current = current->next;
	        }
	    }
	}

    string getDrinksOrder(int drinkOrder) const {
        if (drinkOrder >= 1 && drinkOrder <= NUM_ordersdrink) {
            return DrinksOrder[drinkOrder - 1];
        } else {
            return "Unknown Drink Order";
        }
    }

    void displayDrinksMenu() const {
        cout << "Drinks Menu :\n";
        for (int i = 0; i < NUM_ordersdrink; ++i) {
            cout << i + 1 << ". " << DrinksOrder[i] << endl;
        }
        cout << NUM_ordersdrink + 1 << ". Cancel" << endl;
    }

    void cleanupDrinkQueue() {
        while (!drink.empty()) {
            Node* temp = drink.front();
            drink.pop();
            delete temp;
        }

        while (!tempQueue.empty()) {
            Node* temp = tempQueue.front();
            tempQueue.pop();
            delete temp;
        }
    }

    ~DrinkQueue() override {
        cleanupDrinkQueue();
    }
    
    void displayRemovedData() const {
        if (tempQueue.empty()) {
            cout << "No data has been removed.\n\n";
        } else {
            Node* current = tempQueue.front();
            cout << "Deleted Order : \n";
            while (current != nullptr) {
            	if (current->deleted){
            		cout << "\nName: " << current->customerInfo.name << endl;
	                cout << "Drink Order : " << getDrinksOrder(current->customerInfo.drinkOrder) << endl;
	                cout << "Order Quantity : " << current->customerInfo.drinkQuantity << endl;
	                int orderIndex = current->customerInfo.drinkOrder - 1;
	                cout << "Total Payment : " << drink_price[orderIndex] * current->customerInfo.drinkQuantity << endl;
				}
                current = current->next;
            }
            cout << endl;
        }
    }

    
    bool hasRemovedData() const {
        return !tempQueue.empty();
    }
};

int main(){
	Customer ticketCust;
	Customer fCust;
	Customer dCust;
	TicketQueue tQueue;
	FoodQueue fQueue;
	DrinkQueue dQueue;
	int choice, choiceOrder, movieChoice, showtimeChoice, foodChoice, foodOrder, foodQuantity, drinkOrder, drinkQuantity,detail, detailfd, hpsOrder, hpsfd;
	do{
	cout<<"========== FAMSY CINETHIQUE ==========\n";
	cout << "\nMenu :\n" ;
    cout << "1. Add Customer\n" ;
    cout << "2. Delete Customer\n" ;
    cout << "3. Detail Orders\n" ;
    cout << "4. Exit\n" ;
    cout << "Option: ";
    cin>>choice;
    if(cin.fail()){
			cout<<"Invalid Option.\n\n";
			cin.clear();
			cin.ignore();
	}else{
		switch(choice){
    	case 1:system("cls");{
    		cout<<"========== FAMSY CINETHIQUE ==========\n";
    		cout << "\nChoose Order :\n";
   			cout << "1. Book Movie Ticket\n";
    		cout << "2. Order Food and Drink\n";
    		cout << "3. Cancel\n";
    		cout << "Option : ";
			cin>>choiceOrder;
			if(cin.fail()){
				cout<<"Invalid Option.\n\n";
				cin.clear();
				cin.ignore();
			}else{
				switch(choiceOrder){
					case 1:system("cls");{
						cout<<"Customer Name : ";
						cin.ignore();
                		getline(cin,ticketCust.name);
                		cout << "\nList Film :" << endl;
					    for (int i = 0; i < NUM_choiceMovie; ++i) {
						cout << i + 1 << ". " << MovieChoices[i] << endl;
								    }
						cout<< NUM_choiceMovie + 1 << ". Cancel" << endl;
					    cout << "Option : ";
					    cin>>ticketCust.movieChoice;
					    	if(cin.fail()){
								cout<<"Invalid Option.\n\n";
								cin.clear();
								cin.ignore();
							}else{
								switch(ticketCust.movieChoice){
									case 1:system("cls");{
									cout << "~~~ The SpongeBob Movie : Sponge on the Run ~~~\n";
						            cout << "Choose Your Movie Time :" << endl;
						            for (int i = 0; i < NUM_SHOWTIMES; ++i) {
								    cout << i + 1 << ". " << SHOWTIME_DESCRIPTION[i] << endl;
								    }
								    cout<< NUM_SHOWTIMES + 1 << ". Cancel" << endl;
						            cout<<"Option : ";
						            cin>>ticketCust.showtimeChoice;
						            if(cin.fail()){
										cout<<"Invalid Option.\n\n";
										cin.clear();
										cin.ignore(); 
									}else{
										switch(ticketCust.showtimeChoice){
											case 1:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 2:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 3:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 4:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											
											case 5 :system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 6 :{
												cout<<"Canceling...\n\n";
												break;
											}
											default:{
												cout<<"Invalid Option.\n\n";
												break;
											}
										}
									}
								break;	
								}
								
								case  2: system("cls");{
									cout << "~~~ One Piece Film : Red ~~~\n";
						            cout << "Choose Your Movie Time :" << endl;
						            for (int i = 0; i < NUM_SHOWTIMES; ++i) {
								    cout << i + 1 << ". " << SHOWTIME_DESCRIPTION[i] << endl;
								    }
						            cout <<NUM_SHOWTIMES + 1 << ". Cancel" << endl;
						            cout<<"Option : ";
						            cin>>ticketCust.showtimeChoice;
						            if(cin.fail()){
										cout<<"Invalid Option.\n\n";
										cin.clear();
										cin.ignore();
									}else{
										switch(ticketCust.showtimeChoice){
											case 1:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 2:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 3:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 4:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 5: system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 6:{
												cout<<"Canceling...\n\n";
												break;
											}
											default:{
												cout<<"Invalid Option.\n\n";
												break;
											}
									}}
									break;
								
								}
								case 3:system("cls");{
									cout << "~~~ Tom and Jerry : Snowman's Land ~~~\n";
						           cout << "Choose Your Movie Time :" << endl;
						            for (int i = 0; i < NUM_SHOWTIMES; ++i) {
								    cout << i + 1 << ". " << SHOWTIME_DESCRIPTION[i] << endl;
								    }
						            cout <<NUM_SHOWTIMES + 1 << ". Cancel" << endl;
						            cout<<"Option : ";
						            cin>>ticketCust.showtimeChoice;
						            if(cin.fail()){
										cout<<"Invalid Option.\n\n";
										cin.clear();
										cin.ignore();
									}else{
										switch(ticketCust.showtimeChoice){
											case 1:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 2:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 3:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 4:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore(); 
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 5: system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 6:{
												cout<<"Canceling...\n\n";
												break;
											}
											default:{
												cout<<"Invalid Option.\n\n";
												break;
											}	
									}}
									break;
								}
								case 4:system("cls");{
									cout << "~~~ Doraemon The Movie : Nobita's Little Star Wars 2021 ~~~\n";
						            cout << "Choose Your Movie Time :" << endl;
						            for (int i = 0; i < NUM_SHOWTIMES; ++i) {
								    cout << i + 1 << ". " << SHOWTIME_DESCRIPTION[i] << endl;
								    }
						            cout <<NUM_SHOWTIMES + 1 << ". Cancel" << endl;
						            cout<<"Option : ";
						            cin>>ticketCust.showtimeChoice;
						            if(cin.fail()){
										cout<<"Invalid Option.\n\n";
										cin.clear();
										cin.ignore();
									}else{
										switch(ticketCust.showtimeChoice){
											case 1:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 2:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 3:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 4:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 5:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 6:{
												cout<<"Canceling...\n\n";
												break;
											}
											default:{
												cout<<"Invalid Option.\n\n";
												break;
											}	
									}}
									break;
								}
								case 5:system("cls");{
									cout << "~~~ Sofia The First : The Buttercups ~~~\n";
						            cout << "Choose Your Movie Time :" << endl;
						            for (int i = 0; i < NUM_SHOWTIMES; ++i) {
								    cout << i + 1 << ". " << SHOWTIME_DESCRIPTION[i] << endl;
								    }
						            cout <<NUM_SHOWTIMES + 1 << ". Cancel" << endl;
						            cout<<"Option : ";
						            cin>>ticketCust.showtimeChoice;
						            if(cin.fail()){
										cout<<"Invalid Option.\n\n";
										cin.clear();
										cin.ignore();
									}else{
										switch(ticketCust.showtimeChoice){
											case 1:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 2:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 3:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 4:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
											case 5:system("cls");{
												cout << "Ticket Quantity : ";
						                        cin >> ticketCust.ticketOrder;
						                        if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
												}else{
													string seatNumber[ticketCust.ticketOrder];
						                        	for (int i = 0; i < ticketCust.ticketOrder; ++i) {
						                        	cout << "Insert Seat Number " << i + 1 << ": ";
						      						  cin >> seatNumber[i];
						    						}
													cout<<"Total Payment : "<<ticketCust.ticketOrder * ticket_price;
	                                				tQueue.enqueue(ticketCust);
												}
												break;
											}
												
											case 6:{
												cout<<"Canceling...\n\n";
												break;
											
											}
											default:{
												cout<<"Invalid Option.\n\n";
												break;
											}
										}
									}
									break;
								}
								case 6:{
									cout<<"Canceling...\n\n";
									break;
								}
								
								default:{
									cout<<"Invalid Option.\n\n";
									break;
								}
							}
						break;
					}
					break;
				}
				case 2:system("cls");{
					cout << "Menu :\n";
				    cout << "1. Food\n";
				    cout << "2. Drink\n";
				    cout << "3. Cancel\n";
				    cout<<"Option : ";
				    cin>>foodChoice;
				    if(cin.fail()){
						cout<<"Invalid Option.\n\n";
						cin.clear();
						cin.ignore();
					}else{
						switch(foodChoice){
							case 1:system("cls");{
								cout<<"Customer Name : ";
								cin.ignore();
			                	getline(cin,fCust.name);
			                	cout<<endl;
							    fQueue.displayFoodsMenu();
							    cout<<"Option : ";
							    cin>>fCust.foodOrder;
							    fCust.foodOrders.push_back(fCust.foodOrder);
							   if (cin.fail() || fCust.foodOrder < 1 || fCust.foodOrder > NUM_ordersfood + 1) {
       							 cout << "Invalid Option.\n\n";
        						 cin.clear();
        						 cin.ignore();
								}else{
									switch(fCust.foodOrder){
										case 1:{
											cout<<"\nOrder Quantity : ";
											cin>>fCust.foodQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore(); 
											}else{
												cout<<"Total Payment : "<<food_price[0] * fCust.foodQuantity;
												fQueue.enqueue(fCust);
											}cout<<endl;
											break;
										}
										case 2:{
											cout<<"\nOrder Quantity : ";
											cin>>fCust.foodQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore(); 
											}else{
												cout<<"Total Payment : "<<food_price[1] * fCust.foodQuantity;
												fQueue.enqueue(fCust);
											}cout<<endl;
											break;
										}
										case 3:{
											cout<<"\nOrder Quantity : ";
											cin>>fCust.foodQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<<food_price[2] * fCust.foodQuantity;
												fQueue.enqueue(fCust);
											}cout<<endl;
											break;
										}
										case 4:{
											cout<<"\nOrder Quantity : ";
											cin>>fCust.foodQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<<food_price[3] * fCust.foodQuantity;
												fQueue.enqueue(fCust);
											}cout<<endl;
											break;
										}
										case 5:{
											cout<<"\nOrder Quantity : ";
											cin>>fCust.foodQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<<food_price[4] * fCust.foodQuantity;
												fQueue.enqueue(fCust);
											}cout<<endl;
											break;
										}
										case 6:{
											cout<<"Canceling...\n\n";
											break;
										}
										default:{
											cout<<"Invalid Option.\n\n";
											break;
										}
										
									}
								}
								break;
							}
							case 2:system("cls");{
								cout<<"Customer Name : ";
								cin.ignore();
			                	getline(cin,dCust.name);
								cout<<endl;
								dQueue.displayDrinksMenu();
							    cout << "Option : ";
							    cin>>dCust.drinkOrder;
							    dCust.drinkOrders.push_back(dCust.drinkOrder);
							     if (cin.fail() || dCust.drinkOrder < 1 || dCust.drinkOrder > NUM_ordersdrink + 1) {
									cout<<"Invalid Option.\n\n";
									cin.clear();
									cin.ignore();
								}else{
									switch(dCust.drinkOrder){
										case 1:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[0] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 2:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[1] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 3:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[2] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 4:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore(); 
											}else{
												cout<<"Total Payment : "<< drink_price[3] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 5:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[4] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 6:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[5] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}
											break;
										}
										case 7:{
											cout<<"\nOrder Quantity : ";
											cin>>dCust.drinkQuantity;
											if(cin.fail()){
													cout<<"Invalid Input.\n\n";
													cin.clear();
													cin.ignore();
											}else{
												cout<<"Total Payment : "<< drink_price[6] * dCust.drinkQuantity;
												dQueue.enqueue(dCust);
											}cout<<endl;
											break;
										}
										case 8:{
											cout<<"Canceling...\n\n";
											break;
										}
										default:{
											cout<<"Invalid Option.\n\n";
											break;
										}		
								}
							}break;
						}
						case 3:{
							cout<<"Canceling...\n\n";
							break;
						}
						default:{
							cout<<"Invalid Option.\n\n";
							break;
						}
					}
				}break;
			}
		}
	}break;
		}
		case 2:system("cls");{
			cout<<"========== FAMSY CINETHIQUE ==========\n";
			cout<<"\nDelete : \n";
          	cout<<"1. Ticket Order\n";
           	cout<<"2. Food and Drink Order\n";
           	cout<<"3. Cancel\n";
            cout<<"Option : ";
            cin>>hpsOrder;
            if(cin.fail()){
				cout<<"Invalid Option.\n\n";
				cin.clear();
				cin.ignore();
			}else{
				switch(hpsOrder){
					case 1:{
						tQueue.dequeue();
						break;
					}
					case 2:system("cls");{
						cout<<"Choose :\n";
						cout<<"1. Food\n";
						cout<<"2. Drink\n";
						cout<<"3. Cancel\n";
						cout<<"Option : ";
						cin>>hpsfd;
						if(cin.fail()){
							cout<<"Invalid Option.\n\n";
							cin.clear();
							cin.ignore();
						}else{
							switch(hpsfd){
								case 1:{
									fQueue.dequeue();cout<<endl;
									break;
								}
								case 2:{
									dQueue.dequeue();cout<<endl;
									break;
								}
								case 3:{
									cout<<"Canceling...\n\n";
									break;
								}
								default:{
									cout<<"Invalid Option.\n\n";
									break;
								}
							}
						}
						break;
					}
					case 3:{
						cout<<"Canceling...\n\n";
						break;
					}
					default:{
						cout<<"Invalid Option.\n\n";
						break;
					}
				}
			}
            
			break;
		}
				case 3:system("cls");{
					cout<<"========== FAMSY CINETHIQUE ==========\n";
					cout<<"\nDisplay : \n";
                	cout<<"1. Detail Orders Ticket\n";
                	cout<<"2. Detail Orders Food and Drink\n";
                	cout<<"3. Cancel\n";
                	cout<<"Option : ";
                	cin>>detail;
                	if(cin.fail()){
						cout<<"Invalid Option.\n\n";
						cin.clear();
						cin.ignore();
					}else{
						switch(detail){
	                		case 1:system("cls");{
	                			cout << "Order Queue : \n";
							    tQueue.displayQueue();
	                			if (tQueue.hasRemovedData()) {
							        tQueue.displayRemovedData();
							    }
								break;
							}
							case 2:system("cls");{
								cout<<"Choose :\n";
								cout<<"1. Food\n";
								cout<<"2. Drink\n";
								cout<<"3. Cancel\n";
								cout<<"Option : ";
								cin>>detailfd;
								if(cin.fail()){
									cout<<"Invalid Option.\n\n";
									cin.clear();
									cin.ignore();
								}else{
									switch(detailfd){
										case 1:system("cls");{
											cout << "Order Queue : \n";
											fQueue.displayQueue(); cout<<endl;
											if (fQueue.hasRemovedData()) {
							       				fQueue.displayRemovedData();
							    			}
											break;
										}
										case 2:system("cls");{cout << "Order Queue : \n";
											dQueue.displayQueue(); cout<<endl;
											if (dQueue.hasRemovedData()) {
							       				dQueue.displayRemovedData();
							    			}
											break;
										}
										case 3:{
											cout<<"Canceling...\n\n";
											break;
										}
										default:{
											cout<<"Invalid Option.\n\n";
											break;
										}
									}
								}
								break;
							}
							case 3 :{
								cout<<"Canceling...\n\n";
								break;
							}
							default:{
								cout<<"Invalid Option.\n\n";
								break;
							}
		}
	}break;
}
		case 4:{
			cout<<"Exit...\n";
			break;
		}
		default:{
			cout<<"Invalid Option.\n\n";
			break;
		}
			
    
	}
	
}
}while(choice!=4);
return 0;
}