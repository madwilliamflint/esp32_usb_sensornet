#!/bin/bash

# Ensure the project.info file exists
if [ ! -f "project.info" ]; then
    echo "Error: project.info file does not exist."
    exit 1
fi

# Generate the ProjectInfo.h header file
cat <<EOT > ./include/ProjectInfo.h
#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#define PROJECT_NAME "$(grep 'PROJECT_NAME' project.info | cut -d '=' -f2)"
#define AUTHOR "$(grep 'AUTHOR' project.info | cut -d '=' -f2)"
#define VERSION "$(grep 'VERSION' project.info | cut -d '=' -f2)"
#define BUILD_NUMBER "$(grep 'BUILD_NUMBER' project.info | cut -d '=' -f2)"
#define LAST_UPDATE "$(grep 'LAST_UPDATE' project.info | cut -d '=' -f2)"
#define HOSTNAME "$(grep 'HOSTNAME' project.info | cut -d '=' -f2)"

#endif
EOT

echo "ProjectInfo.h generated successfully."
