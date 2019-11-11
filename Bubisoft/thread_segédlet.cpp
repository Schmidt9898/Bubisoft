#include <iostream>
#include <thread>
#include  <mutex>
#include <condition_variable>

using namespace std;

   std::mutex adam;/// mutex olyan mint a monitor javaban
   std::mutex monitor;
   std::condition_variable monitor_c; /// mutexre nem lehet waitelni se notifyolni
                                      ///ezért kell egy olyan valami amire lehet ,különbség
                                      ///,hogy ezt nem lehet másolni ezért kell külön

void func(int * a)///sima szinkronizáció csak mutexel
{
    adam.lock();
    *a += 1;
    cout<<"helo az a: "<<*a<<endl;
    adam.unlock();
}


void f(string smg){///szinkronizálás waitingel
while(true){


monitor.lock();
cout<<"thread " << smg <<" waiting"<<endl;
monitor.unlock();

unique_lock<std::mutex> lk(monitor);///also locking it so no need to lock again
                                    /// ja és nem is lehetne mert deadlock lesz



monitor_c.wait(lk);///ameddig wait el addig nem fogja a monitort.
///itt viszaszerzi a lock ot
//std::condition_variable::wait(lk);///not good

//monitor.lock();
this_thread::sleep_for(chrono::milliseconds(1000));///alszik
cout<<"thread " << smg <<" waiting over"<<endl;
monitor.unlock();///felold


}

}



int main()
{
    cout << "Hello world!" << endl;

   /* int * a= new int(5);
    thread szal(func,a);
    func(a);
    szal.join();
*/

thread szal1(f,"1");///szálat így hívsz f a függvény minden más a paraméter ez a sor után egybõl fut.
thread szal2(f,"2");
thread szal3(f,"3");

string s;

while(true){
    monitor.lock();
        cout<<"pres any enter"<<endl;
monitor.unlock();
cin>>s;
cout<<s<<endl;
monitor.lock();
monitor_c.notify_all();
monitor.unlock();



}





    cout<<"the end"<<endl;
    return 0;
}
