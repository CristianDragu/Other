"""
This module represents a device.

Computer Systems Architecture Course
Assignment 1
March 2016
"""

from threading import Event, Thread, Semaphore, Lock

class ReusableBarrier(object):
    """
    Bariera reentranta (exact ca in laborator)
    """
    def __init__(self, num_threads):
        self.num_threads = num_threads
        self.count_threads1 = [self.num_threads]
        self.count_threads2 = [self.num_threads]
        self.count_lock = Lock()
        self.threads_sem1 = Semaphore(0)
        self.threads_sem2 = Semaphore(0)

    def wait(self):
        """
        wait apeleaza metoda phase
        """
        self.phase(self.count_threads1, self.threads_sem1)
        self.phase(self.count_threads2, self.threads_sem2)

    def phase(self, count_threads, threads_sem):
        """
        phase
        """
        with self.count_lock:
            count_threads[0] -= 1
            if count_threads[0] == 0:
                for i in range(self.num_threads):
                    threads_sem.release()
                count_threads[0] = self.num_threads
        threads_sem.acquire()

class ScriptThread(Thread):
    """
    Clasa ce extinde Thread cu scopul de a paraleliza calculele
    facute pentru obtinerea noii valori dintr-o locatie.
    Fiecare thread este creat pentru o pereche (script, locatie).
    """
    def __init__(self, script, location, device, neighbours):
        """
        Constructor
        """
        Thread.__init__(self)
        self.script = script
        self.location = location
        self.device = device
        self.neighbours = neighbours

    def run(self):
        """
        In aceasta metoda se fac calculele pentru obtinerea noii valori
        din locatia curenta, apoi valoarea este scrisa in rezultatele
        tutror vecinilor, dar si in cel local device-ului curent.
        """
        self.device.hash_locatie[self.location].acquire()

        script_data = []
        for device in self.neighbours:
            data = device.get_data(self.location)
            if data is not None:
                script_data.append(data)
        data = self.device.get_data(self.location)
        if data is not None:
            script_data.append(data)

        if script_data != []:
            result = self.script.run(script_data)

            self.device.lock.acquire()
            for device in self.neighbours:
                device.set_data(self.location, result)
            self.device.set_data(self.location, result)
            self.device.lock.release()

        self.device.hash_locatie[self.location].release()

class Device(object):
    """
    Class that represents a device.
    """

    def __init__(self, device_id, sensor_data, supervisor):
        """
        Constructor.

        @type device_id: Integer
        @param device_id: the unique id of this node; between 0 and N-1

        @type sensor_data: List of (Integer, Float)
        @param sensor_data: a list containing (location, data)
                            as measured by this device

        @type supervisor: Supervisor
        @param supervisor: the testing infrastructure's control
                            and validation component
        """
        self.device_id = device_id
        self.sensor_data = sensor_data
        self.supervisor = supervisor
        self.script_received = Event()
        self.scripts = []
        self.timepoint_done = Event()
        self.thread = DeviceThread(self)
        self.barrier = None
        self.lock = None
        self.hash_locatie = None
        self.thread.start()

    def __str__(self):
        """
        Pretty prints this device.

        @rtype: String
        @return: a string containing the id of this device
        """
        return "Device %d" % self.device_id

    def setup_devices(self, devices):
        """
        In aceasta metoda setez deviceurile cu valorile initiale.
        Am folosit o idee asemanatoare singleton pattern pentru
        instantierea barierei, si lock-urilor ce trebuiesc a fi
        partajate de toate device-urile.
        hash_locatie -> pentru fiecare location am cate un lock
        self.lock -> folosit pentru scrierea de date in ScriptThread
        """
        if self.device_id == devices[0].device_id:
            barrier = ReusableBarrier(len(devices))
            my_lock = Lock()
            hash_locatie = {}
            for i in range(101):
                hash_locatie[i] = Lock()
            self.barrier = barrier
            self.lock = my_lock
            self.hash_locatie = hash_locatie
            for device in devices:
                if device.barrier is None:
                    device.barrier = barrier
                if device.lock is None:
                    device.lock = my_lock
                if device.hash_locatie is None:
                    device.hash_locatie = hash_locatie

    def assign_script(self, script, location):
        """
        Provide a script for the device to execute.

        @type script: Script
        @param script: the script to execute from now on at each timepoint;
                        None if the current timepoint has ended

        @type location: Integer
        @param location: the location for which the script is interested in
        """
        if script is not None:
            self.scripts.append((script, location))
            self.script_received.set()
        else:
            self.timepoint_done.set()

    def get_data(self, location):
        """
        Returns the pollution value this device has for the given location.

        @type location: Integer
        @param location: a location for which obtain the data

        @rtype: Float
        @return: the pollution value
        """
        if location in self.sensor_data:
            return self.sensor_data[location]
        else:
            return None

    def set_data(self, location, data):
        """
        Sets the pollution value stored by this device for the given location.

        @type location: Integer
        @param location: a location for which to set the data

        @type data: Float
        @param data: the pollution value
        """
        if location in self.sensor_data:
            self.sensor_data[location] = data

    def shutdown(self):
        """
        Instructs the device to shutdown (terminate all threads). This method
        is invoked by the tester. This method must block until all the threads
        started by this device terminate.
        """
        self.thread.join()

class DeviceThread(Thread):
    """
    Class that implements the device's worker thread.
    """

    def __init__(self, device):
        """
        Constructor.

        @type device: Device
        @param device: the device which owns this thread
        """
        Thread.__init__(self, name="Device Thread %d" % device.device_id)
        self.device = device

    def run(self):
        # hope there is only one timepoint, as multiple iterations
        # of the loop are not supported
        while True:
            # get the current neighbourhood
            neighbours = self.device.supervisor.get_neighbours()
            if neighbours is None:
                break

            self.device.timepoint_done.wait()

            script_list = []

            # creez cate un thread pentru fiecare pereche (script, location)
            for (script, location) in self.device.scripts:
                script_list.append(ScriptThread(script,
                                                location,
                                                self.device,
                                                neighbours))

            # pornesc threadurile
            for thread in script_list:
                thread.start()

            # inchei procesarea pe threaduri a scripturilor primite
            for thread in script_list:
                thread.join()

            # hope we don't get more than one script
            self.device.timepoint_done.clear()
            self.device.barrier.wait()
