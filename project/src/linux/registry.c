/* ************************************************************************ */
/*																			*/
/*  Systool - a Neko VM library												*/
/*  Copyright (c)2006														*/
/*  Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom					*/
/*																			*/
/* This library is free software; you can redistribute it and/or			*/
/* modify it under the terms of the GNU Lesser General Public				*/
/* License as published by the Free Software Foundation; either				*/
/* version 2.1 of the License, or (at your option) any later version.		*/
/*																			*/
/* This library is distributed in the hope that it will be useful,			*/
/* but WITHOUT ANY WARRANTY; without even the implied warranty of			*/
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU		*/
/* Lesser General Public License or the LICENSE file for more details.		*/
/*																			*/
/* ************************************************************************ */

#include <gconf/gconf-client.h>

#ifdef __cplusplus
extern "C" {
#endif

static GConfClient *getRegistry()
{
    static GConfClient *sRegistry = NULL;
    if ( sRegistry == NULL )
    {
		sRegistry = gconf_client_get_default();
    }
    return sRegistry;
}

gchar *makeGConfKey( const char *subkey, const char *valuename ) {
	char *result = NULL;
	if( valuename ) {
		result = g_strdup_printf("/%s/%s",subkey,valuename);
	} else {
		result = g_strdup_printf("/%s",subkey);
	}
	char *r = result;
	while( r[0] ) {
		if( r[0]=='\\' ) r[0]='/';
		r++;
	}
	return result;
}

void gconf_client_unset_recursive( GConfClient *client, const char *dir ) {
	// recursively unset directories
	GSList *list = gconf_client_all_dirs( client, dir, NULL );
	while( list ) {
		const char *key = (const char *)list->data;
		gconf_client_unset_recursive( client, key );
		g_free( list->data );
		list = list->next;
	}
	g_slist_free( list );
	
	// unset keys in this directory
	list = gconf_client_all_entries( client, dir, NULL );
	while( list ) {
		const char *key = ((GConfEntry *)list->data)->key;
		gconf_client_unset( client, key, NULL );
		g_free( list->data );
		list = list->next;
	}
	g_slist_free( list );
}

void systools_registry_set_value(int _, const char *subkey, const char *valuename, const char *value) {
	gchar *key = makeGConfKey( subkey, valuename );
	gconf_client_set_string( getRegistry(), key, value, NULL );
	g_free( key );
}

char* systools_registry_get_value( int _, const char *subkey, const char *valuename ) {
	gchar *key = makeGConfKey( subkey, valuename );
	char *result = gconf_client_get_string( getRegistry(), key, NULL );
	g_free( key );
	return result;
}

void systools_registry_delete_key( int _, const char * subkey ) {	
	gchar *key = makeGConfKey( subkey, NULL );
	gconf_client_unset_recursive( getRegistry(), key );
	g_free( key );
}
#ifdef __cplusplus
}
#endif
