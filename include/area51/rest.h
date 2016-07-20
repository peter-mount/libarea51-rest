/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rest.h
 * Author: peter
 *
 * Created on 20 July 2016, 22:19
 */

#ifndef AREA51_REST_H
#define AREA51_REST_H

#include <area51/charbuffer.h>
#include <area51/list.h>

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * Append an int value to a buffer. If the value is INT_MIN then null is written
     * @param b
     * @param v
     */
    extern void json_append_int(struct charbuffer *b, int v);
    /**
     * Append a string to a buffer. If null then null will be written
     * @param b
     * @param s
     */
    extern void json_append_str(struct charbuffer *b, char *s);

    /**
     * Write a List as an array
     * @param b charbuffer
     * @param l List
     * @param appender method to write a Node to the charbuffer
     */
    extern void json_append_list(struct charbuffer *b, struct List *l, void (*appender)(struct charbuffer *, struct Node *));

    /**
     * Add a handler that will perform an int search.
     * 
     * Given a prefix of say "/stanox" then this will call a method for any url like "/stanox/1234"
     * passing it 1234 as an int parameter
     *
     * @param prefix URL prefix, e.g. "/stanox"
     * @param map Hashmap with int keys
     * @param search meth
     */
    extern void webserver_add_search_int(const char *prefix, void (*search)(struct charbuffer *, int value));

    extern void webserver_add_search_str(const char *prefix, void (*search)(struct charbuffer *, const char *value));
#ifdef __cplusplus
}
#endif

#endif /* AREA51_REST_H */

