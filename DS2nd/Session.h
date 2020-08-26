#ifndef __SESSION__
#define __SESSION__

typedef struct InfoSession *InfoSessionPtr;

InfoSessionPtr SessionNew(char *);
void SessionNewTab(InfoSessionPtr);

/* The rest of the interface functions follow */



void SessionTabShow(InfoSessionPtr Session);
void SessionTabNext(InfoSessionPtr Session);
void SessionTabPrev(InfoSessionPtr Session);
void SessionTabMoveLeft(InfoSessionPtr Session);
void SessionTabMoveRight(InfoSessionPtr Session);
void SessionNewOpeningAddress(InfoSessionPtr Session,char *string);
void SessionShowOpeningAddress(InfoSessionPtr Session);
void SessionSiteNext(InfoSessionPtr Session);
void SessionSitePrev(InfoSessionPtr Session);
void SessionSiteShow(InfoSessionPtr Session);
void SessionTabClose(InfoSessionPtr *Session);
void SessionClose(InfoSessionPtr *Session);
void SessionNewAddress(InfoSessionPtr Session,char *Address);
void remove_newline_ch(char *line);
int get_option();
void print_options(void);
int get_session();
void print_session(void);


#endif
