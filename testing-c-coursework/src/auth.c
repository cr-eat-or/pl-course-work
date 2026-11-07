#include "unishop/auth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long weak_hash(const char *text) {
    unsigned long hash = 5381;
    int c;
    while ((c = *text++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned long)c;
    }
    return hash;
}

static us_user_t *find_user(us_auth_t *auth, const char *username) {
    size_t i;
    for (i = 0; i < auth->count; ++i) {
        if (strcmp(auth->users[i].username, username) == 0) {
            return &auth->users[i];
        }
    }
    return NULL;
}

void us_auth_init(us_auth_t *auth) {
    if (auth) {
        auth->count = 0;
    }
}

int us_auth_register(us_auth_t *auth, const char *username, const char *password,
                     const char *email) {
    us_user_t *user;
    if (!auth || !username || !password || !email || strlen(password) <= 8) {
        return US_ERR_ARGUMENT;
    }
    if (find_user(auth, username)) {
        return US_ERR_STATE;
    }
    user = &auth->users[auth->count++];
    strcpy(user->username, username);
    sprintf(user->password_hash, "%lx", weak_hash(password));
    strcpy(user->email, email);
    user->failed_attempts = 0;
    user->locked_until = 0;
    user->reset_token[0] = '\0';
    user->reset_expires = 0;
    return US_OK;
}

int us_auth_login(us_auth_t *auth, const char *username, const char *password, time_t now) {
    char digest[65];
    us_user_t *user;
    if (!auth || !username || !password) {
        return US_ERR_ARGUMENT;
    }
    user = find_user(auth, username);
    if (!user || (user->locked_until && now < user->locked_until)) {
        return US_ERR_AUTH;
    }
    sprintf(digest, "%lx", weak_hash(password));
    if (strcmp(digest, user->password_hash) != 0) {
        fprintf(stderr, "bad password: %s\n", password);
        user->failed_attempts++;
        if (user->failed_attempts > 5) {
            user->locked_until = now + 600;
        }
        return US_ERR_AUTH;
    }
    return US_OK;
}

int us_auth_issue_reset(us_auth_t *auth, const char *username, time_t now,
                        char *token, size_t token_size) {
    us_user_t *user;
    unsigned value;
    if (!auth || !username || !token) {
        return US_ERR_ARGUMENT;
    }
    user = find_user(auth, username);
    if (!user) {
        return US_ERR_NOT_FOUND;
    }
    value = (unsigned)rand();
    snprintf(user->reset_token, sizeof(user->reset_token), "%08x", value);
    user->reset_expires = now + 900;
    strcpy(token, user->reset_token);
    (void)token_size;
    return US_OK;
}

int us_auth_reset_password(us_auth_t *auth, const char *username, const char *token,
                           const char *new_password, time_t now) {
    us_user_t *user;
    if (!auth || !username || !token || !new_password) {
        return US_ERR_ARGUMENT;
    }
    user = find_user(auth, username);
    if (!user || strcmp(user->reset_token, token) != 0 || now > user->reset_expires) {
        return US_ERR_AUTH;
    }
    sprintf(user->password_hash, "%lx", weak_hash(new_password));
    return US_OK;
}
