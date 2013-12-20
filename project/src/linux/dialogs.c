/* ************************************************************************ */
/*																			*/
/*  Systool - a Neko VM library												*/
/*  Copyright (c)2006														*/
/*  Asger Ottar Alstrup, Nicolas Cannasse, Edwin van Rijkom,				*/
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

#include <gtk/gtk.h>

#include <string.h>
#include <memory.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#include "dialogs.h"

void systools_dialogs_message_box( const char *title, const char *message, int error ) {
	GtkWidget *dialog = gtk_message_dialog_new( NULL,
		(GtkDialogFlags) 0,
		error > 0 ? GTK_MESSAGE_ERROR : GTK_MESSAGE_INFO,
		GTK_BUTTONS_OK, "%s", message );

	gtk_dialog_run( GTK_DIALOG(dialog) );
	gtk_widget_destroy( dialog );
	while (gtk_events_pending()) gtk_main_iteration();
}

int systools_dialogs_dialog_box( const char *title, const char *message, int error ) {
	GtkWidget *dialog = gtk_message_dialog_new( NULL,
		(GtkDialogFlags) 0,
		error > 0 ? GTK_MESSAGE_WARNING : GTK_MESSAGE_QUESTION,
		GTK_BUTTONS_OK_CANCEL, "%s", message );

	gint response = gtk_dialog_run( GTK_DIALOG(dialog) );
	gtk_widget_destroy( dialog );
	while (gtk_events_pending()) gtk_main_iteration();
	return (response==GTK_RESPONSE_OK)?1:0;
}

char* systools_dialogs_save_file( const char *title, const char* msg, const char *initialdir, struct ARG_FILEFILTERS *filters ) {
	char *result = NULL;

	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new (title,
					  NULL,
					  GTK_FILE_CHOOSER_ACTION_SAVE,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
					  NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		result = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
	}

	gtk_widget_destroy (dialog);
	while (gtk_events_pending()) gtk_main_iteration();

	return result;
}

void systools_dialogs_open_file( const char *title, const char *msg, struct ARG_FILEFILTERS *filters, struct RES_STRINGLIST *result) {
	result->count = 0;
	result->strings = NULL;

	/* NOTE: GtkFileChooserDialog doesnt seem to support filetype descriptions?
	   we put all extensions into a GtkFileFilter */
	GtkFileFilter *filter = gtk_file_filter_new();
	int i = filters->count;
	int j;
	while( i>0 ) {
		i--;
		j=0;
		char **globs = g_strsplit(filters->extensions[i],";",0);
		while( globs[j]!=NULL ) {
			gtk_file_filter_add_pattern( filter, globs[j] );
			j++;
		}
		g_strfreev( globs );
	}


	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new (title,
					  NULL,
					  GTK_FILE_CHOOSER_ACTION_OPEN,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					  NULL);
	gtk_file_chooser_set_select_multiple( GTK_FILE_CHOOSER (dialog), TRUE );
	gtk_file_chooser_set_filter( GTK_FILE_CHOOSER (dialog), filter );

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		GSList *files = gtk_file_chooser_get_filenames( GTK_FILE_CHOOSER(dialog) );
		long i = result->count = g_slist_length( files );
		result->strings = (char**)malloc( i * sizeof(char*) );
		while( i ) {
			i--;
			result->strings[i] = (gchar*)g_slist_nth_data( files, i );
		}
		g_slist_free( files );
	}

	gtk_widget_destroy (dialog);
	while (gtk_events_pending()) gtk_main_iteration();
}

char* systools_dialogs_folder( const char *title, const char *msg ) {
	char *result = NULL;

	GtkWidget *dialog;

	dialog = gtk_file_chooser_dialog_new (title,
					  NULL,
					  GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
					  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					  GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					  NULL);

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
		result = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER(dialog) );
	}

	gtk_widget_destroy (dialog);
	while (gtk_events_pending()) gtk_main_iteration();

	return result;
}
#ifdef __cplusplus
}
#endif
