# frontend/Dockerfile
FROM nginx:alpine

# Remove the default Nginx configuration
RUN rm -v /etc/nginx/nginx.conf

# Copy custom Nginx configuration
COPY nginx.conf /etc/nginx/

# Set the working directory inside the container
WORKDIR /usr/share/nginx/html

# Copy the frontend files into the container
COPY ./ /usr/share/nginx/html

# Expose port 3001
EXPOSE 3001

# Start Nginx in the foreground
CMD ["nginx", "-g", "daemon off;"]