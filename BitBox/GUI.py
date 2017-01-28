#!/usr/bin/python

from gi.repository import Gtk, Gdk, Gio, GObject
import Client
from File import File
from User import User
import os
import cPickle as pickle

class MainWindow(Gtk.Window):
    def __init__(self):
        Gtk.Window.__init__(self, title="BitBox")
        self.resize(640, 480)
        self.set_size_request(640, 480)
        self.set_resizable(False)
        self.authentification()

        header_bar = Gtk.HeaderBar()
        header_bar.set_show_close_button(True)
        header_bar.props.title = "BitBox"

        header_bar.set_visible(False)

        self.set_titlebar(header_bar)

        users = Gtk.Button(label="Users")
        users.connect("clicked", self.list_users)
        share = Gtk.Button(label="Share")
        share.connect("clicked", self.share_folder)
        history = Gtk.Button(label="History")
        history.connect("clicked", self.show_history)

        header_bar.pack_start(users)
        header_bar.pack_start(share)
        header_bar.pack_start(history)

        self.vbox = None
        self.connected = False

        self.history_list = []

    def authentification(self):

        self.listbox = Gtk.ListBox()
        self.listbox.set_selection_mode(Gtk.SelectionMode.NONE)
        self.add(self.listbox)

        for i in range(6):
            empty_row = Gtk.ListBoxRow()
            empty_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL)
            empty_label = Gtk.Label("")
            empty_box.add(empty_label)
            empty_row.add(empty_box)
            self.listbox.add(empty_row)

        # username

        hbox = Gtk.HBox()
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        label = Gtk.Label("Username")
        box.add(label)
        self.user_text_field = Gtk.Entry()
        box.add(self.user_text_field)
        self.user_text_field.set_width_chars(20)
        hbox.pack_start(label, False, False, 0)
        hbox.pack_start(box, False, False, 0)
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        self.listbox.add(hbox)

        # password

        hbox = Gtk.HBox()
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=16)
        label = Gtk.Label("Password")
        box.add(label)
        self.pswd_text_field = Gtk.Entry()
        self.pswd_text_field.set_width_chars(20)
        self.pswd_text_field.set_visibility(False)
        box.add(self.pswd_text_field)
        hbox.pack_start(label, False, False, 0)
        hbox.pack_start(box, False, False, 0)
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        self.listbox.add(hbox)

        # server-ip

        hbox = Gtk.HBox()
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=16)
        label = Gtk.Label("Server-IP")
        box.add(label)
        self.ip_text_field = Gtk.Entry()
        box.add(self.ip_text_field)
        self.ip_text_field.set_width_chars(20)
        hbox.pack_start(label, False, False, 0)
        hbox.pack_start(box, False, False, 0)
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        self.listbox.add(hbox)

        # port

        hbox = Gtk.HBox()

        hbox.pack_start(Gtk.Label(''), True, False, 0)
        big_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=22)
        label = Gtk.Label("Port")
        big_box.add(label)
        box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL)
        button = Gtk.Button()
        box.add(button)
        button.add(Gtk.Arrow(Gtk.ArrowType.LEFT, Gtk.ShadowType.NONE))
        button.connect("clicked", self.decrease_port)

        self.port_text_field = Gtk.Entry()
        box.add(self.port_text_field)
        self.port_text_field.set_text("4243")
        self.port_text_field.set_width_chars(7)

        button = Gtk.Button()
        box.add(button)
        button.add(Gtk.Arrow(Gtk.ArrowType.RIGHT, Gtk.ShadowType.NONE))
        button.connect("clicked", self.increase_port)
        big_box.add(box)
        hbox.pack_start(big_box, False, False, 0)
        hbox.pack_start(Gtk.Label(''), True, False, 0)

        self.listbox.add(hbox)

        # connect button

        connect = Gtk.Button(label="Connect")
        connect.connect("clicked", self.clicked_connect)

        hbox = Gtk.HBox()
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        hbox.pack_start(connect, False, False, 0)
        hbox.pack_start(Gtk.Label(''), True, False, 0)
        self.listbox.add(hbox)

    def decrease_port(self, widget):
        if int(self.port_text_field.get_text()) > 4243:
            self.port_text_field.set_text(str(int(self.port_text_field.get_text()) - 1))

    def increase_port(self, widget):
        self.port_text_field.set_text(str(int(self.port_text_field.get_text()) + 1))

    def clicked_connect(self, widget):
        self.user = self.user_text_field.get_text()
        self.password = self.pswd_text_field.get_text()
        self.ip = self.ip_text_field.get_text()
        self.port = int(self.port_text_field.get_text())
        Client.connect(self.ip)
        if Client.auth(self.user, self.password, self.port):
            print "connected"
            self.connected = True
            self.after_auth()
        else:
            print "get fcked"

    def get_users(self, widget=None):
        self.users = Client.getUsers()

    def get_files(self, username):
        user = User.findUser(self.users, username)
        user.files = Client.getFiles(username)

    def after_auth(self):
        self.remove(self.listbox)

        user_files = File.getFileStruct(None, os.getcwd())
        File.printFiles(user_files)
  
        Client.s.sendall(pickle.dumps(user_files,-1))

        Client.dest_dir = os.getcwd()
        server_init = Client.ServerInitializer(0, self.port)
        server_init.start()
        self.list_users()

    def hbytes(self, num):
        for x in ['bytes','KB','MB','GB']:
            if num < 1024.0:
                return "%3.1f%s" % (num, x)
            num /= 1024.0
        return "%3.1f%s" % (num, 'TB')

    def on_timeout(self, progressbar, transfer):
        """
        Update value on the progress bar
        """
        if self.activity_mode:
            progressbar.pulse()
        else:
            if progressbar.get_fraction() < 1.0:
                progressbar.set_fraction(transfer.getProgress())
            else:
                return False

        return True


    def list_users(self, widget=None):
        if self.connected == True:
            if self.vbox is not None:
                self.remove(self.vbox)

            self.scrolled_window1 = Gtk.ScrolledWindow()
            self.scrolled_window1.set_size_request(640, 300)
            self.scrolled_window1.set_border_width(10)

            self.vbox = Gtk.VBox(orientation=Gtk.Orientation.VERTICAL)
            self.add(self.vbox)

            self.vbox.pack_start(self.scrolled_window1, True, True, 0)
            self.scrolled_window1.show()

            self.userslist = Gtk.ListBox()
            self.userslist.set_selection_mode(Gtk.SelectionMode.NONE)
            self.scrolled_window1.add(self.userslist)

            self.scrolled_window1.add_with_viewport(self.userslist)
            self.userslist.show()

            self.get_users()

            for i in range(len(self.users)):
                user_row = Gtk.ListBoxRow()
                user = Gtk.Button(label=self.users[i].name)
                user.connect("clicked", self.list_files, self.users[i].name, None)
                user.show()
                user_row.add(user)
                self.userslist.add(user_row)

            self.header_transfer = Gtk.ListBox()
            self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)
            header_frame = Gtk.Frame()
            header_dl = Gtk.HBox()
            header_dl.add(Gtk.Label('File Name'))
            header_dl.add(Gtk.Label('  Progress        '))
            header_dl.add(Gtk.Label('Size'))
            header_dl.add(Gtk.Label('Owner'))
            header_frame.add(header_dl)
            header_frame.show()
            self.header_transfer.add(header_frame)
            self.vbox.pack_start(self.header_transfer, True, True, 0)
            self.header_transfer.show()

            self.scrolled_window2 = Gtk.ScrolledWindow()
            self.scrolled_window2.set_border_width(1)

            self.vbox.pack_start(self.scrolled_window2, True, True, 0)
            self.scrolled_window2.show()

            self.transfer_list = Gtk.ListBox()
            self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)

            self.scrolled_window2.add_with_viewport(self.transfer_list)
            self.transfer_list.show()

            for transfer in Client.transfers:
                dl_row = Gtk.HBox()
                file_name = Gtk.Label(transfer.file.name.split('/')[-1][0:20])
                file_name.set_max_width_chars(20)
                file_name.set_width_chars(20)
                dl_row.pack_start(file_name, False, False, 0)
                # progress bar
                progressbar = Gtk.ProgressBar()
                self.timeout_id = GObject.timeout_add(50, self.on_timeout, progressbar, transfer)
                self.activity_mode = False
                dl_row.pack_start(progressbar, True, True, 0)
                dl_row.pack_start(Gtk.Label(str(self.hbytes(transfer.file.size))), True, True, 0)
                dl_row.pack_start(Gtk.Label(transfer.user.name), True, True, 0)
                self.transfer_list.add(dl_row)

            self.show_all()

    def list_files(self, widget=None, *data):
        if self.vbox is not None:
            self.remove(self.vbox)

        username = data[0]
        foldername = data[1]
        print username
        self.scrolled_window1 = Gtk.ScrolledWindow()
        self.scrolled_window1.set_size_request(640, 300)
        self.scrolled_window1.set_border_width(10)

        self.vbox = Gtk.VBox(orientation=Gtk.Orientation.VERTICAL)
        self.add(self.vbox)

        self.vbox.pack_start(self.scrolled_window1, True, True, 0)
        self.scrolled_window1.show()

        self.userslist = Gtk.ListBox()
        self.userslist.set_selection_mode(Gtk.SelectionMode.NONE)
        self.scrolled_window1.add(self.userslist)

        self.scrolled_window1.add_with_viewport(self.userslist)
        self.userslist.show()

        self.get_files(username)
        user = User.findUser(self.users, username)

        if foldername is None:
            for file in user.files:
                user_row = Gtk.ListBoxRow()
                user = Gtk.Button(label=file.name)
                user.connect("clicked", self.list_files, username, file)
                user.show()
                user_row.add(user)
                self.userslist.add(user_row)

        else:
            if not foldername.files == []:
                for file in foldername.files:
                    user_row = Gtk.ListBoxRow()
                    user = Gtk.Button(label=file.name)
                    user.connect("clicked", self.list_files, username, file)
                    user.show()
                    user_row.add(user)
                    self.userslist.add(user_row)
            else:
                dialog = Gtk.FileChooserDialog("Select a folder", self, Gtk.FileChooserAction.SELECT_FOLDER,
                                               ("Cancel", Gtk.ResponseType.CANCEL,
                                                "Select", Gtk.ResponseType.OK))

                response = dialog.run()
                if response == Gtk.ResponseType.OK:
                    Client.dest_dir = dialog.get_filename()

                    transfer = Client.Transfer(user, foldername)
                    Client.transfers.append(transfer)
                    self.history_list.append(transfer.file.name)
                    transfer.start()

                dialog.destroy()

        self.header_transfer = Gtk.ListBox()
        self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)
        header_frame = Gtk.Frame()
        header_dl = Gtk.HBox()
        header_dl.add(Gtk.Label('File Name'))
        header_dl.add(Gtk.Label(' Progress        '))
        header_dl.add(Gtk.Label('Size'))
        header_dl.add(Gtk.Label('Owner'))
        header_frame.add(header_dl)
        header_frame.show()
        self.header_transfer.add(header_frame)
        self.vbox.pack_start(self.header_transfer, True, True, 0)
        self.header_transfer.show()

        self.scrolled_window2 = Gtk.ScrolledWindow()
        self.scrolled_window2.set_border_width(1)

        self.vbox.pack_start(self.scrolled_window2, True, True, 0)
        self.scrolled_window2.show()

        self.transfer_list = Gtk.ListBox()
        self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)

        self.scrolled_window2.add_with_viewport(self.transfer_list)
        self.transfer_list.show()

        for transfer in Client.transfers:
            dl_row = Gtk.HBox()
            file_name = Gtk.Label(transfer.file.name.split('/')[-1][0:20])
            file_name.set_max_width_chars(20)
            file_name.set_width_chars(20)
            dl_row.pack_start(file_name, False, False, 0)
            # progress bar
            progressbar = Gtk.ProgressBar()
            self.timeout_id = GObject.timeout_add(50, self.on_timeout, progressbar, transfer)
            self.activity_mode = False
            dl_row.pack_start(progressbar, True, True, 0)
            dl_row.pack_start(Gtk.Label(str(self.hbytes(transfer.file.size))), True, True, 0)
            dl_row.pack_start(Gtk.Label(transfer.user.name), True, True, 0)
            self.transfer_list.add(dl_row)

        self.show_all()

    #Button to select the folder in which files will be shared
    def share_folder(self, widget=None):
        if self.connected == True:
            dialog = Gtk.FileChooserDialog("Select a folder", self, Gtk.FileChooserAction.SELECT_FOLDER,
                                           ("Cancel", Gtk.ResponseType.CANCEL,
                                            "Select", Gtk.ResponseType.OK))

            response = dialog.run()

            user_files = File.getFileStruct(None, dialog.get_filename())
            File.printFiles(user_files)
            Client.user_files = user_files

            Client.updateFiles()
            dialog.destroy()

    def show_history(self, widget=None):
        print 'im insadasdaada'
        if self.connected == True:
            if self.vbox is not None:
                self.remove(self.vbox)

            self.scrolled_window1 = Gtk.ScrolledWindow()
            self.scrolled_window1.set_size_request(640, 300)
            self.scrolled_window1.set_border_width(10)

            self.vbox = Gtk.VBox(orientation=Gtk.Orientation.VERTICAL)
            self.add(self.vbox)

            self.vbox.pack_start(self.scrolled_window1, True, True, 0)
            self.scrolled_window1.show()

            self.userslist = Gtk.ListBox()
            self.userslist.set_selection_mode(Gtk.SelectionMode.NONE)
            self.scrolled_window1.add(self.userslist)

            self.scrolled_window1.add_with_viewport(self.userslist)
            self.userslist.show()

            for i in self.history_list:
                history_row = Gtk.ListBoxRow()
                history_row.add(Gtk.Label(i))
                self.userslist.add(history_row)

            self.header_transfer = Gtk.ListBox()
            self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)
            header_frame = Gtk.Frame()
            header_dl = Gtk.HBox()
            header_dl.add(Gtk.Label('File Name'))
            header_dl.add(Gtk.Label('  Progress        '))
            header_dl.add(Gtk.Label('Size'))
            header_dl.add(Gtk.Label('Owner'))
            header_frame.add(header_dl)
            header_frame.show()
            self.header_transfer.add(header_frame)
            self.vbox.pack_start(self.header_transfer, True, True, 0)
            self.header_transfer.show()

            self.scrolled_window2 = Gtk.ScrolledWindow()
            self.scrolled_window2.set_border_width(1)

            self.vbox.pack_start(self.scrolled_window2, True, True, 0)
            self.scrolled_window2.show()

            self.transfer_list = Gtk.ListBox()
            self.header_transfer.set_selection_mode(Gtk.SelectionMode.NONE)

            self.scrolled_window2.add_with_viewport(self.transfer_list)
            self.transfer_list.show()

            for transfer in Client.transfers:
                dl_row = Gtk.HBox()
                file_name = Gtk.Label(transfer.file.name.split('/')[-1][0:20])
                file_name.set_max_width_chars(20)
                file_name.set_width_chars(20)
                dl_row.pack_start(file_name, False, False, 0)
                # progress bar
                progressbar = Gtk.ProgressBar()
                self.timeout_id = GObject.timeout_add(50, self.on_timeout, progressbar, transfer)
                self.activity_mode = False
                dl_row.pack_start(progressbar, True, True, 0)
                dl_row.pack_start(Gtk.Label(str(self.hbytes(transfer.file.size))), True, True, 0)
                dl_row.pack_start(Gtk.Label(transfer.user.name), True, True, 0)
                self.transfer_list.add(dl_row)

            self.show_all()


if __name__ == "__main__":
    window = MainWindow()
    window.connect("delete-event", Client.signal_handler)
    window.show_all()
    Gtk.main()