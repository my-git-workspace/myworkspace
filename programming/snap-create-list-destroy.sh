#!/bin/bash
count=100
for n in {1..100}; do
sudo zfs snapshot  qnappool/fs1@snap$n
done

for n in {1..100}; do
sudo zfs list  qnappool/fs1@snap$n
done

for n in {1..100}; do
sudo zfs destroy  qnappool/fs1@snap$n
done
