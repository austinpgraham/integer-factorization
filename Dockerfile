FROM g++:4.9
COPY . /prod-factor
WORKDIR /prod-factor
RUN make prod-build
CMD ["./prod-factor"]
