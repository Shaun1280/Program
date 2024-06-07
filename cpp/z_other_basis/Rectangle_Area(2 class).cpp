#include <iostream>

using namespace std;
/*
 * Create classes Rectangle and RectangleArea
 */
class Rectangle{
	public:
		virtual void display() const{
			cout<<width<<" "<<height<<endl;
		}
	
	protected:
		int width;
		int height;
};
class RectangleArea : public Rectangle{
	public:
		void display() const override{
		cout<<(width*height)<<endl;
		}
		void read_input(){
			cin>>width>>height;
		}	
};
/*************************************************/
/*
struct Rectangle {
	int w, h;
	void Display() {
		printf("%d %d\n", w, h);
	}
};
struct RectangleArea : Rectangle {
	void Input() {
		scanf("%d%d", &w, &h);
	}
	void Display() {
		printf("%d\n", w * h);
	}
};
*/
/*************************************************/
/*
class Rectangle {
    protected:
    int width, height;
    public:
       void Display(){
           cout<<width<<' '<<height<<endl;
       }
};

class RectangleArea : public Rectangle {
    public:
    
       void Input() {
           cin>>width>>height;
       }
       void Display(){
           cout<<width*height;
       }
};
*/
int main()
{
    RectangleArea r_area;
 
    r_area.read_input();
 
    r_area.Rectangle::display();

    r_area.display();
    
    return 0;
}
