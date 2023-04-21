#!/usr/bin/env bash
# Copyright (c) 2023 The Brave Authors. All rights reserved.
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at https://mozilla.org/MPL/2.0/.

# Helper to check if the script is sourced or not.
__is_sourced() {
  if [ -n "$ZSH_VERSION" ]; then
    case $ZSH_EVAL_CONTEXT in
    *:file:*)
      return 0
      ;;
    esac
  else
    case ${0##*/} in
    dash | -dash | bash | -bash | ksh | -ksh | sh | -sh)
      return 0
      ;;
    esac
  fi
  return 1 # NOT sourced.
}

# Do nothing if the script wasn't sourced.
if ! __is_sourced; then
  unset __is_sourced
  echo Please source the file: . $0
  exit 1
fi
unset __is_sourced

# Get environment variables to update.
if [ -n "$ZSH_VERSION" ]; then
  __env_vars=$(node $(dirname "$0")/build/commands/scripts/genEnv.js)
else
  __env_vars=$(node $(dirname "$BASH_SOURCE")/build/commands/scripts/genEnv.js)
fi

# Set/unset environment variables. Vars to unset use `var=` syntax.
while IFS=$'\n' read line; do
  if [[ $line =~ ^([^=]+)=(.*)$ ]]; then
    if [[ "$1" == "-v" ]]; then
      echo $line
    fi

    if [ -n "$ZSH_VERSION" ]; then
      key=${match[1]}
      val=${match[2]}
    else
      key=${BASH_REMATCH[1]}
      val=${BASH_REMATCH[2]}
    fi

    if [[ -z "$val" ]]; then
      unset $key
    else
      export $key="$val"
    fi
  fi
done <<<$__env_vars

unset __env_vars
