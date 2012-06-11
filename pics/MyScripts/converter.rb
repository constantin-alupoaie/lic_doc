class Converter
	def convert config
		cmd = "convert #{config[:ipath]} -resize #{config[:size]}! #{config[:opath]}"
		system cmd
	end
end





