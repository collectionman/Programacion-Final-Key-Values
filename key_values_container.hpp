/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContainerKeyValues.hpp
 * Author: Julián Martín Llorensi
 *
 * Created on 4 de agosto de 2018, 00:27
 */

#ifndef KEY_VALUES_CONTAINER_HPP
#define KEY_VALUES_CONTAINER_HPP

#ifndef COLLECTION_HPP
    #include "collection.hpp"
#endif

template < typename KeyType, typename ValueType >
struct KeyValuesMap
{
    /*
     *  Cada clave tiene una colección de valores:
     * 
     *  { KEY - 0 : VALUES[ 0 ] }& -> VALUES[ 0 ].ITEMS { VAL0, VAL1, VAL2, ... }
     *  { KEY - 1 : VALUES[ 1 ] }& -> VALUES[ 1 ].ITEMS {  "  ,  "  ,  "  , ... }
     *  { KEY - 2 : VALUES[ 2 ] }& -> VALUES[ 2 ].ITEMS {  "  ,  "  ,  "  , ... }
     */
    
    enum { TOTAL_OF_BINDINGS = 512 } ;
    
    Collection<KeyType> itsKeys ;
    Collection<ValueType> itsCollectionsOfValues[ TOTAL_OF_BINDINGS ] ;
    
    void init( void ) ;
    void release( void ) ;
    void reset( void ) ;
    
    void add( const KeyType& key, const ValueType& value ) ;
    void add( const KeyValueMap<KeyType,ValueType>& pair ) ;
    
    size_t size( void ) ;
    
    Collection<KeyType> keys( void ) const ;
    
    Collection<ValueType>& itemsAtPos( const KeyType& key ) ;
    Collection<ValueType> valuesForKey( const KeyType& key ) ;
    
    KeyType* firstItem( void ) ;
    KeyType* nextItem( void ) ;
    
    bool contain( const KeyType& key ) ;
};

template < typename KeyType, typename ValueType >
void KeyValuesMap<KeyType,ValueType>::init( void )
{
    itsKeys.init() ;
    for ( size_t i = 0; i < TOTAL_OF_BINDINGS; i++ ) 
    {
        // Inicializa cada una de las colecciones
        itsCollectionsOfValues[ i ].init() ;
    }
}

template < typename KeyType, typename ValueType >
void KeyValuesMap<KeyType,ValueType>::release( void )
{
    itsKeys.release() ;
    for ( size_t i = 0; i < TOTAL_OF_BINDINGS; i++ )
    {
        itsCollectionsOfValues[ i ].release() ;
    }
}

template < typename KeyType, typename ValueType >
void KeyValuesMap<KeyType,ValueType>::reset( void )
{
    itsKeys.reset() ;
    for ( size_t i = 0; i < TOTAL_OF_BINDINGS; i++ )
    {
        itsCollectionsOfValues[ i ].reset() ;
    }
}

template < typename KeyType, typename ValueType >
void KeyValuesMap<KeyType,ValueType>::add( const KeyType& key, const ValueType& values )
{
    long slot = itsKeys.indexOf( key ) ;
    if ( slot == -1 ) {
        itsKeys.add( key ) ;
        slot = itsKeys.indexOf( key ) ;
    } // else only add the values
    itsCollectionsOfValues[ slot ].add( value ) ;
}

template < typename KeyType, typename ValueType >
void KeyValuesMap<KeyType,ValueType>::add( const KeyValuesMap<KeyType,ValueType>& pair )
{
    ;
}

template < typename KeyType, typename ValueType >
size_t KeyValuesMap<KeyType,ValueType>::size( void )
{
    return itsKeys.size() ;
}

template < typename KeyType, typename ValueType >
Collection<KeyType> KeyValuesMap<KeyType,ValueType>::keys( void ) const
{
    return itsKeys ;
}

template < typename KeyType, typename ValueType >
Collection<ValueType>& KeyValuesMap<KeyType,ValueType>::itemsAtPos( const KeyType& key )
{
    long slot = itsKeys.indexOf( key ) ;
    
    if ( slot == -1 ) {
        itsKeys.add( key ) ;
        slot = itsKeys.indexOf( key ) ;
        itsCollectionsOfValues[ slot ] = Collection<ValueType>() ;
    } 
    
    return itsCollectionsOfValues[ slot ] ;
}

template < typename KeyType, typename ValueType >
Collection<ValueType> KeyValuesMap<KeyType,ValueType>::valuesForKey( const KeyType& key )
{
    long slot = itsKeys.indexOf( key ) ;
    return ( slot != -1 ) ? itsCollectionsOfValues[ slot ] : Collection<ValueType>() ;
}

template < typename KeyType, typename ValueType >
KeyType* KeyValuesMap<KeyType,ValueType>::firstItem( void )
{
    return itsKeys.firstItem() ;
}

template < typename KeyType, typename ValueType >
KeyType* KeyValuesMap<KeyType,ValueType>::nextItem( void )
{
    return itsKeys.nextItem() ;
}

template < typename KeyType, typename ValueType >
bool KeyValuesMap<KeyType,ValueType>::contain( const KeyType& key )
{
    return itsKeys.contain( key ) ;
}

#endif /* CONTAINERKEYVALUES_HPP */

