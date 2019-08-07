/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Julián Martín Llorensi
 *
 * Created on 4 de agosto de 2018, 00:25
 */

#include <stdlib.h>
#include "collection.hpp"
#include "ansi_string.hpp"

struct Reader
{
    typedef const char* SetOfChars ;
    
    enum State { idle, working, binding, end } ;
    State currentState ;
    
    int count ;
    
    Collection<char> alphabet ;
    Collection<char> delimiterKey ;
    Collection<char> delimiterValue ;
    Collection<char> delimiterBinding ;
    Collection<char> endOfInput ;
    
    void  init( SetOfChars alphabet, SetOfChars delimiterKey, 
                SetOfChars delimiterValue, SetOfChars delimiterBinding, 
                SetOfChars endOfInput )
    {
        currentState = idle ;
        count = 0 ;
        
        this->alphabet.init( alphabet, strlen( alphabet ) ) ;
        this->delimiterKey.init( delimiterKey, strlen( delimiterKey ) ) ;
        this->delimiterValue.init( delimiterValue, strlen( delimiterValue ) ) ;
        this->delimiterBinding.init( delimiterBinding, strlen( delimiterBinding ) ) ;
        this->endOfInput.init( endOfInput, strlen( endOfInput ) ) ;
    }
    
    void release( void )
    {
        alphabet.release() ;
        delimiterKey.release() ;
        delimiterValue.release() ;
        delimiterBinding.release() ;
        endOfInput.release() ;
    }
    
    void reset( void )
    {
        count = 0 ;
        currentState = idle ;
    }
    
    AnsiString read( Collection<int>& collectionOfValues )
    {   
        AnsiString key ; key.init() ; 
        bool reading = true ;
        
        while ( reading )
        {
            if ( currentState == idle )
            {
                char ch = std::cin.get() ;
                if ( endOfInput.contain( ch ) )
                {
                    reading = false ;
                }
                else if ( alphabet.contain( ch ) )
                {
                    key.concat( ch ) ;
                    count++ ;
                    currentState = working ;
                }
                else if ( delimiterKey.contain( ch ) || delimiterValue.contain( ch ) || delimiterBinding.contain( ch ) )
                {
                    continue ;
                }
            }
            else if ( currentState == working )
            {
                char ch = std::cin.get() ;
                if ( endOfInput.contain( ch ) )
                {
                    reading = false ;
                    currentState = end ;
                }
                else if ( alphabet.contain( ch ) )
                {
                    key.concat( ch ) ;
                }
                else if ( delimiterKey.contain( ch ) )
                {
                    currentState = binding ;
                }
                else if ( delimiterValue.contain( ch ) || delimiterBinding.contain( ch ) )
                {
                    continue ;
                }
            }
            else if ( currentState == binding )
            {
                AnsiString value ; value.init() ;
                char ch = std::cin.get() ;
                
                if ( endOfInput.contain( ch ) )
                {
                    currentState = end ;
                }
                else if ( delimiterValue.contain( ch ) )
                {
                    collectionOfValues.add( atoi( value.c_string() ) ) ;
                }
                else if ( delimiterBinding.contain( ch ) )
                {
                    if ( !value.isNull() )
                    {
                        ;
                    }
                    else
                    {
                        collectionOfValues.add( atoi( value.c_string() ) ) ;
                        currentState = idle ;
                    }
                }
                else if ( ch >= '0' && ch <= '9' )
                {
                    value.concat( ch ) ;
                    currentState = binding ;
                }
            }
            else if ( currentState == end )
            {
                reading = false ;
                currentState = idle ;
            }
        }
        
        return key ;
    }
    
    int keysReaded( void )
    {
        return count ;
    }
    
    State state( void )
    {
        return currentState ;
    }
    
};

int main(int argc, char** argv) 
{
    /*
     *  GRAMATICA:
     * 
     *  KEY_0 = VALUE, VALUE& KEY_1 = VALUE, VALUE, VALUE,...&
     */
    
    /*
    typedef const char* SetOfChars ;
    
    SetOfChars alphabet = "abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ" ;
    SetOfChars delimiterKey = "=" ;
    SetOfChars delimiterValue = "," ;
    SetOfChars delimiterBinding = "&" ;
    SetOfChars endOfInput = "|" ;
    
    Reader reader ;
    reader.init( alphabet, delimiterKey, delimiterValue, delimiterBinding, endOfInput ) ;
    
    KeyValuesMap<AnsiString,int> associations ;
    
    Collection<int> collectionOfValues ; collectionOfValues.init() ;
    AnsiString key ; key.init() ;
    
    while ( !key.assign( reader.read( collectionOfValues ) ).isNull() )
    {             
        if ( !( associations.contain( key ) ) )
        {
            associations.add( key, collectionOfValues ) ;
            collectionOfValues.release() ;
        }
    }
    
    Collection<AnsiString> keys ; keys.init() ;
    keys.assign( associations.keys() ) ;
    
    AnsiString* currentKey = keys.firstItem() ; 
    while ( currentKey )
    {
        std::cout << "Clave: " << currentKey -> c_string() << std::endl ;
        std::cout << "Valores asociados: " ; associations.itemsAtPos( *currentKey ).dump() ; std::cout << std::endl ;
        currentKey = keys.nextItem() ;
    }
    */
    
    /*
    AnsiString key ; key.init() ;
    Collection<int> listOfValues ; listOfValues.init() ;
    int values[] = {1,2,3,4,5} ;
    listOfValues.add( values, 5 ) ;
    
    KeyValuesMap<AnsiString,int> associations ; associations.init() ;
    
    associations.add( key.assign( "A" ), listOfValues ) ;
    
    AnsiString* currentKey ;
    currentKey = associations.firstItem() ;
    while( currentKey )
    {
        std::cout << "KEY: " << currentKey->c_string() << std::endl ;
        std::cout << "VALUES: " ; associations.itemsAtPos( *currentKey ).dump() ;
        currentKey = associations.nextItem() ;
    }
    */
    
    Collection<int> collection ; collection.init() ;
    int values[] = { 1, 33, 4, 50 } ;
    
    collection.add( values, 4 ) ;
    
    collection.dump() ;
    
    return 0 ;
}

