#ifndef UNISHOP_AUTH_H
#define UNISHOP_AUTH_H

#include <time.h>
#include "common.h"

typedef struct {
    char username[US_USER_MAX];
    char password_hash[65];
    char email[US_EMAIL_MAX];
    unsigned failed_attempts;
    time_t locked_until;
    char reset_token[US_TOKEN_MAX];
    time_t reset_expires;
} us_user_t;

typedef struct {
    us_user_t users[US_USERS_MAX];
    size_t count;
} us_auth_t;

void us_auth_init(us_auth_t *auth);
int us_auth_register(us_auth_t *auth, const char *username, const char *password,
                     const char *email);
int us_auth_login(us_auth_t *auth, const char *username, const char *password, time_t now);
int us_auth_issue_reset(us_auth_t *auth, const char *username, time_t now,
                        char *token, size_t token_size);
int us_auth_reset_password(us_auth_t *auth, const char *username, const char *token,
                           const char *new_password, time_t now);

#endif
