
#include "NumberWithUnits.hpp"
#include <deque>
#include <map>
#include <set>



namespace ariel{

    NumberWithUnits::NumberWithUnits(double _value, std::string _type):value(_value),type(_type){
        map<string, list<string>>::iterator it;
        it = chain_map.find(_type);
        if(it == chain_map.end())
            throw invalid_argument("Invalid unit " + _type + ";");
    }
    NumberWithUnits::NumberWithUnits(int _value, std::string _type):value(_value),type(_type){
        map<string, list<string>>::iterator it;
        it = chain_map.find(_type);
        if(it == chain_map.end())
            throw invalid_argument("Invalid unit " + _type + ";");
    }

    const NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits& n2) const {
        double value = n2.value;
        if(this->type!=n2.type){
            value = covertUnitsChain(n2.type, this->type, n2.value);
        }
        return NumberWithUnits(value+this->value, this->type);
    }

    NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& n2){
        double value1 = n2.value;
        if(this->type!=n2.type){
            value1 = covertUnitsChain(n2.type, this->type, n2.value);
        }
        double temp = this->value + value1;
        this->value = temp;
        return *this;
    }

    const NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits& n2) const{
        double value = n2.value;
        if(this->type!=n2.type){
            value = covertUnitsChain(n2.type, this->type, n2.value);
        }
        return NumberWithUnits(this->value - value, this->type);
    }

    NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& n2){
        double value = n2.value;
        if(this->type!=n2.type){
            value = covertUnitsChain(n2.type, this->type, n2.value);
        }
        this->value -= value;
        return *this;
    }
    bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return abs(n1.value-value)<0.0001;
    }
    bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return n1.value<=value;
    }
    bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return n1.value>=value;
    }
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return n1.value!=value;
    }
    bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return n1.value>value;
    }
    bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2){
        double value = n2.value;
        if(n1.type!=n2.type){
            value = NumberWithUnits::covertUnitsChain(n2.type, n1.type, n2.value);
        }
        return n1.value<value;
    }


    std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n) {
        os << n.value;
        os << "[";
        os << n.type;
        os << "]";
        return os;
    }

    const NumberWithUnits operator*(const double num, const NumberWithUnits& n1){
        return NumberWithUnits(n1.value*num, n1.type);
    }

    const NumberWithUnits operator*(const NumberWithUnits& n1, const double num){
        return NumberWithUnits(n1.value*num, n1.type);
    }

    static std::istream& getAndCheckNextCharIs(std::istream& input, char expectedChar) {
        char actualChar;
        input >> actualChar;
        if (!input) return input;

        if (actualChar!=expectedChar) 
            // failbit is for format error
            input.setstate(ios::failbit);
        return input;
    }


    ifstream& NumberWithUnits::read_units(ifstream& file){
        string line;
        string delimiter = " ";
        int counter = 0; 
        if (file.is_open())
        {
            while (getline(file,line) )
            {
                //catch a problem while reading from file
                try
                {
                    int number_a=0;
                    double number_b=1;
                    string from_unit;
                    string to_unit;
                    string operator_;
                    stringstream ss(line);
                    ss >> number_a >> from_unit >> operator_ >> number_b >> to_unit;
                    
                    pair<string, string> key_pair = make_pair(from_unit, to_unit);
                    values_map.insert({key_pair, number_b});
                    
                    map<string, list<string>>::iterator it;
                    it = chain_map.find(from_unit);

                    if(it != chain_map.end()){
                        chain_map[from_unit].push_back(to_unit);
                    }
                    else{
                        chain_map.insert({from_unit, list<string>{to_unit}});
                    }

                    it = chain_map.find(to_unit);
                    if(it != chain_map.end()){
                        chain_map[to_unit].push_back(from_unit);
                    }
                    else{
                        chain_map.insert({to_unit, list<string>{from_unit}});
                    }

                    
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }
                
            }

            file.close();
        }
        else cout << "Unable to open file"; 
        return file;
    }

    bool isValueExsit(map<string,string> map_, string someKey, string someValue ){
        for (auto it = map_.begin(); it != map_.end(); ++it)
            if (it->second == someValue && it->first == someKey)
                return true;
        return false;
    }


    double NumberWithUnits::covertUnitsChain(string fromUnit, string toUnit, double value){
        map<string, list<string>>::iterator it_chain;
        list<string>::iterator it_list;
        deque<string> visited_q;
        set<string> visited_s;
        map<string, string> parent_map;

        it_chain = chain_map.find(toUnit);
        if(it_chain == chain_map.end()){
            throw invalid_argument("Invalid unit to convert");
        }

        visited_q.push_front(toUnit);
        visited_s.insert(toUnit);

        string last_item = "";
        
        bool flag = false;

        string needUnit = toUnit;
        while(!flag && !visited_q.empty()){
            toUnit = visited_q.front();
            //loop over the list to find if there is a match
            for(it_list = chain_map[toUnit].begin(); it_list != chain_map[toUnit].end()  && !flag; ++it_list){
                
                if(!isValueExsit(parent_map, toUnit, *it_list))
                {
                    parent_map.insert({*it_list, toUnit});
                }

                if(*it_list == fromUnit)
                {
                    flag = true;
                }
                else{
                    if(visited_s.find(*it_list) == visited_s.end()){
                        visited_q.push_back(*it_list);
                        visited_s.insert(*it_list);
                    }
                }


            }
            visited_q.pop_front();
        }
        

        if(flag){
            string temp = "";
            double convert = value;
            while(temp != needUnit){
                temp = parent_map[fromUnit];
                convert = covertUnits(fromUnit, temp, convert);
                fromUnit = temp;
            }
            return convert;
        }

        throw invalid_argument("Invalid unit to convert");

    }


    double NumberWithUnits::covertUnits(string fromUnit, string toUnit, double value){
        pair<string, string> key_pair = make_pair(fromUnit, toUnit);
        pair<string, string> key_pair_reverse = make_pair(toUnit, fromUnit);
        map<pair<string, string>, double>::iterator it;
        

        it = values_map.find(key_pair);
        if(it != values_map.end()){
            return value*it->second;
        }
        it = values_map.find(key_pair_reverse);

        if(it != values_map.end()){
            return value*(1 / (it->second));
        }

        throw invalid_argument("Invalid unit to convert");
    }
    std::istream& operator>> (istream& input, NumberWithUnits& n) {

char ch=0;
        string type;
        double value=1;
        bool error=false;
        ios::pos_type startPosition = input.tellg();
        input>>value;
        input>>ch;
        if(ch != '['){
            error =true;
        }
        input>>type;
        if(type.at(type.length()-1) == ']'){
        string C = type.substr(0,type.length()-1);
        ch = type.at(type.length()-1);
        if( ch != ']'){
            error = true;
        }
        type=C;
        }
        else{
            input>>ch;
            if(ch != ']'){
                error=true;
            }
        }
        map<string, list<string>>::iterator it;
        it = chain_map.find(type);
        if(it == chain_map.end())
            error = true;
        if (error) {
            string str = "Invalid input";
            throw std::invalid_argument(str);
            auto errorState = input.rdstate(); // remember error state
            input.clear(); // clear error so seekg will work
            input.seekg(startPosition); // rewind
            input.clear(errorState); // set back the error flag
        }
    
        n.value=value;
        n.type=type;
    
    
        return input;   

    }
}

